#include <Reader.h>
#include <DeviceConfig.h>
#include <DebugLog.h>
#include <WString.h>
#include <MFRC522.h>
#define RST_PIN 5
#define SS_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

//okuma veya yazma sonucu dönen enumları string olarak döndürür.
char *Reader_Get_Status(MFRC522::StatusCode status, char *logMessage)
{
    String logmMessage = "";
    logmMessage = mfrc522.GetStatusCodeName(status);
    strcpy(logMessage, logmMessage.c_str());
    return logMessage;
}

void Reader_Prepare_Key(Mifare_Auth_Key *key, char _key[KEY_SIZE])
{
    for (byte i = 0; i < 6; i++)
    {
        key->keyByte[i] = _key[i];
    }
}

//set key to mifare card

bool Reader_Mifare_SetKeys(Mifare_Auth_Key *oldkeyA, Mifare_Auth_Key *oldkeyB, Mifare_Auth_Key *newKeyA, Mifare_Auth_Key *newKeyB, int sector)
{
    MFRC522::StatusCode status;
    bool ret = false;
    byte trailerBlock = sector * 4 + 3;
    byte buffer[16] = {0};

    LOG("Authenticating using key A");
    if (0 != Reader_Card_Authenticate(AUTH_KEY_A, trailerBlock, oldkeyA))
    {
        if (newKeyA != NULL)
        {
            memcpy(buffer, newKeyA->keyByte, 6);
        }
    }

    LOG("Authenticating using key B");
    if (0 != Reader_Card_Authenticate(AUTH_KEY_B, trailerBlock, oldkeyB))
    {
        if (newKeyB != NULL)
        {
            memcpy(buffer + KEY_B_POSITION, newKeyB->keyByte, 6);
        }
    }
    status = mfrc522.MIFARE_Write(trailerBlock, buffer, CARD_ROW_SIZE);
    if (status == MFRC522::STATUS_OK)
    {
        ret = true;
    }
    return ret;
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

bool Reader_Card_Authenticate(AUTH_KEYS_type key_type, int trailerBlock, Mifare_Auth_Key *key)
{
    bool ret = false;
    if (AUTH_KEY_A == key_type)
    {
        if (MFRC522::STATUS_OK == mfrc522.PCD_Authenticate(AUTH_KEY_A, trailerBlock, (MFRC522::MIFARE_Key *)key, &(mfrc522.uid)))
        {
            ret = true;
        }
    }
    if (AUTH_KEY_B == key_type)
    {
        if (MFRC522::STATUS_OK == mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, (MFRC522::MIFARE_Key *)key, &(mfrc522.uid)))
        {
            ret = true;
        }
    }
    return ret;
}

bool Reader_WriteBlock(u8 blockNumber, byte data[CARD_ROW_SIZE])
{
    char *logMessage;
    bool ret = false;
    u8 error = 3;
    MFRC522::StatusCode status;

    if (false != Reader_Is_Trailer_Block(blockNumber))
    {
        LOG("Data block a veri yazılamaz");
    }
    else
    {
        while (error < 0)
        {
            status = mfrc522.MIFARE_Write(blockNumber, data, CARD_ROW_SIZE);
            logMessage = Reader_Get_Status(status, logMessage);
            LOG(logMessage);
            if (status != MFRC522::STATUS_OK)
            {
                Reader_Sleep();
                Reader_WakeUp();
                error--;
            }
            else
            {
                ret = true;
                break;
            }
        }
    }
    return ret;
}
bool Reader_ReadBlock(u8 blockNumber, u8 data[CARD_ROW_SIZE])
{
    u8 error = 3;
    char *logMessage;
    bool ret = false;
    MFRC522::StatusCode status;
    byte buffer[CARD_ROW_SIZE + 2];
    byte length = sizeof(buffer);

    while (error < 0)
    {
        status = mfrc522.MIFARE_Read(blockNumber, buffer, &length);
        if (status == MFRC522::STATUS_OK)
        {
            memcpy(data, buffer, CARD_ROW_SIZE);
            ret = true;
            break;
        }
        else
        {
            Reader_Sleep();
            Reader_WakeUp();
            error--;
        }
    }

    Reader_Get_Status(status, logMessage);
    LOG(logMessage);
    return ret;
}

bool Reader_Card_Format()
{
    bool ret = false;
    byte data[16] = {0};
    memset(data, 0, sizeof(data));

    for (u8 i = 0; i < BLOCK_NUMBER; i++)
    {
        if (false != Reader_Is_Trailer_Block(i))
        {
            memcpy(data, DEFAULT_KEY_A, 6);
            memcpy(data + ACCESS_BITS_POSITION, DEFAULT_ACCESS_BITS, 4);
            memcpy(data + KEY_B_POSITION, DEFAULT_KEY_B, 6);
            if (0 != Reader_WriteBlock(i, data))
            {
                ret = true;
            }
        }
        else
        {
            if (0 != Reader_WriteBlock(i, data))
            {
                ret = true;
            }
        }
    }
}

UID_t *Reader_Get_Card_Uid(UID_t *uid)
{
    memcpy(uid->uid, mfrc522.uid.uidByte, mfrc522.uid.size);
    uid->length = mfrc522.uid.size;
    return uid;
}

void example()
{
    bool ret = false;
    char oldKeyData[KEY_SIZE] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    char keyData[KEY_SIZE] = {0xDD, 0xCC, 0xFF, 0xFF, 0xFF, 0xFF};
    u8 block;
    u8 trailer_block;
    u8 data[CARD_ROW_SIZE];
    Mifare_Auth_Key newKeyA;
    Mifare_Auth_Key oldKeyA;

    AUTH_KEYS_type key_type;
    Reader_Task_t task;
    UID_t *uid;

    task = CARD_SET_KEY;
    key_type = AUTH_KEY_A;
    block = 2;
    trailer_block = Reader_Get_Trailer_Block(block);

    memcpy(&oldKeyA.keyByte, oldKeyData, KEY_SIZE);
    Reader_Prepare_Key(&newKeyA, keyData);

    Reader_Init();

    if (0 != Reader_HasCard())
    {
        if (0 != Reader_IsRead_Card())
        {
            if (0 != Reader_IsMifare())
            {

                switch (task)
                {
                case CARD_SET_KEY:
                    Reader_Mifare_SetKeys(&oldKeyA, NULL, &newKeyA, NULL, 1);
                    break;
                case CARD_READ:
                    if (0 != Reader_Card_Authenticate(key_type, trailer_block, &newKeyA))
                    {
                        Reader_ReadBlock(block, data);
                    }
                    break;
                case CARD_WRITE:
                    if (0 != Reader_Card_Authenticate(key_type, trailer_block, &newKeyA))
                    {
                        Reader_WriteBlock(block, data);
                    }
                    break;
                case CARD_FORMAT:
                    if (0 != Reader_Card_Authenticate(key_type, trailer_block, &newKeyA))
                    {
                        Reader_Card_Format();
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}
