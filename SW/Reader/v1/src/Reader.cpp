#include <Reader.h>
#include <MFRC522.h>
#include <LinkedList.h>
#include <Buzzer.h>

#define RST_PIN 5
#define SS_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte sector = 1;
byte blockAddres = 4;
byte trailerBlock = 7;
card_t* card;

void Reader_Prepare_Key()
{
    for(byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }
}
void Reader_Init()
{
    SPI.begin();
    mfrc522.PCD_Init();
    Reader_Prepare_Key();
}

void Reader_Sleep()
{
    //Serial.println("reader sleep");
    digitalWrite(RST_PIN, LOW);
}

void Reader_WakeUp()
{
    //Serial.println("reader wakeup");
    digitalWrite(RST_PIN, HIGH);
}

bool Reader_IsMifare()
{
    bool ret = false;
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    if(piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K)
    {
        //Serial.println(F("Not a Mifare Card."));
        ret = false;
    }
    else
    {
        ret = true;
    }
    return ret;
}


READER_status_t Reader_WriteBlock(int blockNumber, byte arrayAddress[]) 
{
  READER_status_t ret= WRITE_OK;
  MFRC522::StatusCode status;
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModule4Number = blockNumber/4 * 4;
  int trailerBlock = largestModule4Number + 3; //determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber+1)%4 == 0 || blockNumber == 0)
  {
      blockNumber++;
      //Serial.print(blockNumber);Serial.println(" is a trailer block:");
      //ret = READ_ERROR;
  }
  Serial.print(blockNumber);
  Serial.println(" is a data block:");
  
//authentication of the desired block for access
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         ret = READ_ERROR;
  }

  //writing the block
  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
  if (status != MFRC522::STATUS_OK) {
           Serial.print("MIFARE_Write() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           ret = READ_ERROR;
  }
  Serial.println("block was written");
  return ret;
}


READER_status_t Reader_ReadBlock(int blockNumber,byte block[CARD_ROW_SIZE])
{
    MFRC522::StatusCode status;
    byte buffer[18];
    byte bufferSize = sizeof(buffer);
    READER_status_t ret = NOTFOUND;

    if(mfrc522.PICC_IsNewCardPresent())
    {

        if(mfrc522.PICC_ReadCardSerial())
        {
            if(mfrc522.uid.size > 0)
            {
                status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
                if(status == MFRC522::STATUS_OK)
                {
                    Serial.println("authentication successfull");

                    status = mfrc522.MIFARE_Read(blockNumber, buffer, &bufferSize);
                    if(status == MFRC522::STATUS_OK)
                    {
                        Serial.println("Read successfull");
                        ret = READ_OK;
                    }
                }
            }
        }
    }

    return ret;
}

/*void Reader_Fill_List()
{
    passwordList.add(279032257);
    passwordList.add(279038855);
} 
bool Reader_ComparePassword()
{
    bool ret = false;
    //for(int i = 0; i < passwordList.size(); i++)
    {
        //if(card.password == passwordList.get(i))
        {
            ret = true;
            //break;
            //Serial.println(BZR_State);
        }
    }

    //Serial.println(t);
    //BZR_Play_tone();
    return ret;
} */

void READER_stop()
{
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
}

bool READER_handler()
{
    bool ret = false;
    Reader_Fill_List();
    if(READ_OK == Reader_ReadBlock())
    {
        ret = true;
        READER_stop();
        if(false != Reader_ComparePassword())
        {

            BZR_SetAction(BZR_ACTION_ACCESS_CONFIRMED);
            Serial.println("access_conf");
        }
        else
        {
            BZR_SetAction(BZR_ACTION_ACCESS_DENIED);
            Serial.println("access_denied");
        }

    }
    return ret;
}