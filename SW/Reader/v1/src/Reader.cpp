#include <Reader.h>
#include<Buzzer.h>

#define RST_PIN 5
#define SS_PIN 4
//BZR_Tone_t t;

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte sector = 1;
byte blockAddres = 4;
byte trailerBlock = 7;
LinkedList<long> passwordList = LinkedList<long>();
card_t card;

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

READER_status_t Reader_ReadBlock()
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
                status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
                if(status == MFRC522::STATUS_OK)
                {
                    Serial.println("authentication successfull");
                    status = mfrc522.MIFARE_Read(blockAddres, buffer, &bufferSize);
                    if(status == MFRC522::STATUS_OK)
                    {
                        Serial.println("Read successfull");
                        card.password = ((long)buffer[0] << 24) & (0xFFFFFFFF);
                        card.password |= ((long)buffer[1] << 16) & (0xFFFFFF);
                        card.password |= ((long)buffer[2] << 8) & (0xFFFF);
                        card.password |= ((long)buffer[3]) & (0xFF);
                        Serial.print("kart ici sifre= ");
                        Serial.println(card.password);
                        ret = READ_OK;


                    }
                }
            }
        }
    }

    return ret;
}

void Reader_Fill_List()
{
    passwordList.add(279032257);
    passwordList.add(279038855);
}
bool Reader_ComparePassword()
{
    bool ret = false;
    for(int i = 0; i < passwordList.size(); i++)
    {
        if(card.password == passwordList.get(i))
        {
            ret = true;
            break;
            //Serial.println(BZR_State);
        }
    }

    //Serial.println(t);
    //BZR_Play_tone();
    return ret;
}

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