#ifndef __READER_H__
#define __READER_H__

#include "CardConfig.h"

typedef enum
{
    READ_OK,
    WRITE_OK,
    NOTFOUND,
    AUTH_ERROR,
    CAN_NOT_READ_UID,
    UID_LEN_ERROR,
    READ_ERROR
} READER_status_t;

void Reader_Init();
void Reader_Sleep();
void Reader_WakeUp();
bool Reader_IsMifare();
READER_status_t Reader_ReadBlock(int blockNumber,byte block[CARD_ROW_SIZE]);
READER_status_t Reader_WriteBlock(int blockNumber, byte arrayAddress[CARD_ROW_SIZE]);
void Reader_Fill_List();
bool Reader_ComparePassword();     //kart bilgileri gösterilecek
void READER_stop();
bool READER_handler();

#endif // __READER_H__