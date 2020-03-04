#include <MFRC522.h>
#include <SPI.h>
#include<LinkedList.h>

typedef struct UID{
    byte uid[10];
    uint8_t uidlen;
}UID_t;

typedef struct Card{
    UID_t uid;
    uint32_t password;
}card_t;

void Reader_Init();
void Reader_Sleep();
void Reader_WakeUp();
bool Reader_IsMifare();
bool Reader_ReadBlock();     
//void Reader_WriteBlock();
void Reader_Fill_List();
bool Reader_ComparePassword();     //kart bilgileri gösterilecek
void READER_stop();
bool READER_handler();
