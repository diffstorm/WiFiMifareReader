#include <Reader.h>
#include <DeviceConfig.h>

#define RST_PIN 5
#define SS_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void Reader_Prepare_Key(char systemPwd[DEVICE_CFG_NAME_LENGTH])
{
    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = systemPwd[i];
    }
}



//set key to mifare card 
bool Reader_Mifare_SetKeys(byte command, MFRC522::MIFARE_Key *oldKeyA, MFRC522::MIFARE_Key *oldKeyB,
                    MFRC522::MIFARE_Key *newKeyA, MFRC522::MIFARE_Key *newKeyB,
                    int sector)
{
    byte trailerBlock = sector * 4 + 3;
    byte buffer[18];
    byte size = sizeof(buffer);
    if (command == MFRC522::PICC_CMD_MF_AUTH_KEY_A)
    {
        if (0 != Reader_Card_Authenticate(command, trailerBlock, oldKeyA) || 0 != Reader_Card_Authenticate(command, trailerBlock, oldKeyB))
        {
            if (newKeyA != nullptr || newKeyB != nullptr)
            {
                for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++)
                {
                    if (newKeyA != nullptr)
                    {
                        buffer[i] = newKeyA->keyByte[i];
                    }
                    if (newKeyB != nullptr)
                    {
                        buffer[i + 10] = newKeyB->keyByte[i];
                    }
                }
            }
        }
    }
}

void Reader_Init()
{
    SPI.begin();
    mfrc522.PCD_Init();
    //Reader_Prepare_Key();
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

void READER_stop()
{
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
}

bool Reader_IsMifare()
{
    bool ret = false;
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K)
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

bool Reader_HasCard()
{
    bool ret = false;
    if (0 != mfrc522.PICC_IsNewCardPresent())
    {
        ret = true;
    }
    return ret;
}
bool Reader_IsRead_Card()
{
    bool ret = false;
    if (0 != mfrc522.PICC_ReadCardSerial())
    {
        ret = true;
    }
    return ret;
}

u8 Reader_Get_Trailer_Block(int blockNumber)
{
    u8 largestModule4Number = blockNumber / 4 * 4;
    u8 trailerBlock = largestModule4Number + 3; //determine trailer block for the sector
    return trailerBlock;
}

bool Reader_Is_Trailer_Block(int blockNumber)
{
    bool ret = false;
    if (blockNumber > 2 && (blockNumber + 1) % 4 == 0 || blockNumber == 0)
    {
        ret = true;
    }
    return ret;
}

bool Reader_Card_Authenticate(byte command, int trailerBlock, MFRC522::MIFARE_Key *key)
{
    bool ret = false;
    if (command == MFRC522::PICC_CMD_MF_AUTH_KEY_A)
    {
        if (MFRC522::STATUS_OK == mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, key, &(mfrc522.uid)))
            ;
        {
            ret = true;
        }
    }
    if (command == MFRC522::PICC_CMD_MF_AUTH_KEY_B)
    {
        if (MFRC522::STATUS_OK == mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, key, &(mfrc522.uid)))
            ;
        {
            ret = true;
        }
    }

    return ret;
}

READER_status_t Reader_WriteBlock(int blockNumber, byte arrayAddress[])
{
    READER_status_t ret = WRITE_OK;
    MFRC522::StatusCode status;

    if (0 != Reader_Is_Trailer_Block(blockNumber))
    {
        status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, CARD_ROW_SIZE);
        if (status != MFRC522::STATUS_OK)
        {
            Serial.print("MIFARE_Write() failed: ");
            Serial.println(mfrc522.GetStatusCodeName(status));
            ret = WRITE_ERROR;
        }
        else
        {
            ret = WRITE_OK;
        }
    }
    else
    {
        blockNumber++;
    }
    return ret;
}

READER_status_t Reader_ReadBlock(int blockNumber, byte data[CARD_ROW_SIZE], u8 len)
{
    READER_status_t ret = READ_ERROR;
    MFRC522::StatusCode status;

    status = mfrc522.MIFARE_Read(blockNumber, data, &len);
    if (status == MFRC522::STATUS_OK)
    {
        Serial.println("Read successfull");
        ret = READ_OK;
    }
    return ret;
}

bool Reader_Card_Format(u8 sectorNumber, u8 blockSize)
{
    bool ret = false;
    byte data[16];
    memset(data, 0, sizeof(data));

    for (size_t i = 0; i < sectorNumber * 4; i++)
    {
        if (WRITE_OK == Reader_WriteBlock(i, data))
        {
            ret = true;
        }
        else
        {
            ret = false;
            break;
        }
    }
}
