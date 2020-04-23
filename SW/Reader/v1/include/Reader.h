#ifndef __READER_H__
#define __READER_H__

#include "CardConfig.h"

#define SECTOR_NUMBER   16
#define BLOCK_NUMBER (SECTOR_NUMBER)*(4)
#define KEY_SIZE 6

const char DEFAULT_KEY_A[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const char DEFAULT_KEY_B[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const char DEFAULT_ACCESS_BITS[4] = {0x00};

#define KEY_A_POSITION 0
#define ACCESS_BITS_POSITION 6
#define KEY_B_POSITION 10

typedef enum
{
    IDLE,
    CARD_SET_KEY,
    CARD_READ,
    CARD_WRITE,
    CARD_FORMAT,
    NONE
}Reader_Task_t;

typedef enum
{
    AUTH_KEY_A = 0x60,
    AUTH_KEY_B = 0x61
}AUTH_KEYS_type;

typedef struct {
	byte keyByte[KEY_SIZE];
} Mifare_Auth_Key;

void Reader_Prepare_Key(char key[KEY_SIZE]);

bool Reader_Card_Authenticate(AUTH_KEYS_type key_type, int trailerBlock, Mifare_Auth_Key *key);

bool Reader_Mifare_SetKeys(Mifare_Auth_Key* oldkeyA, Mifare_Auth_Key* oldkeyB, Mifare_Auth_Key *newKeyA,Mifare_Auth_Key *newKeyB, int sector);

bool Reader_Card_Format();

bool Reader_WriteBlock(u8 blockNumber, byte data[CARD_ROW_SIZE]);

bool Reader_Is_Trailer_Block(int blockNumber);

bool Reader_ReadBlock(u8 blockNumber, u8 data[CARD_ROW_SIZE]);

UID_t* Reader_Get_Card_Uid(UID_t* uid);

void Reader_Init();

void Reader_Sleep();

void Reader_WakeUp();

bool Reader_IsMifare();

bool Reader_HasCard();

bool Reader_IsRead_Card();

void READER_stop();

u8 Reader_Get_Trailer_Block(int blockNumber);

#endif // __READER_H__