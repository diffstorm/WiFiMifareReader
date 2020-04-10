#ifndef __READER_H__
#define __READER_H__

#include "CardConfig.h"
#include <MFRC522.h>

#define KEY_SIZE 6

typedef enum
{
    READ_OK,
    WRITE_OK,
    NOTFOUND,
    AUTH_ERROR,
    CAN_NOT_READ_UID,
    UID_LEN_ERROR,
    READ_ERROR,
    WRITE_ERROR
} READER_status_t;

void Reader_Prepare_Key(char systemPwd[]);

bool Reader_Mifare_SetKeys(byte command, MFRC522::MIFARE_Key *oldKeyA, MFRC522::MIFARE_Key *oldKeyB);

void Reader_Init();

void Reader_Sleep();

void Reader_WakeUp();

bool Reader_IsMifare();

bool Reader_HasCard();

bool Reader_IsRead_Card();



bool Reader_Card_Authenticate(byte command, int trailerBlock, MFRC522::MIFARE_Key *key);

bool Reader_Is_Trailer_Block(int blockNumber);

READER_status_t Reader_ReadBlock(int blockNumber,byte block[CARD_ROW_SIZE],u8 len);

READER_status_t Reader_WriteBlock(int blockNumber, byte arrayAddress[CARD_ROW_SIZE]);

u8 Reader_Get_Trailer_Block(int blockNumber);


void READER_stop();

bool READER_handler();

#endif // __READER_H__