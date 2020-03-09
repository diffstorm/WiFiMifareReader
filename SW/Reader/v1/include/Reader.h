#include <MFRC522.h>
#include <SPI.h>
#include<LinkedList.h>

typedef struct {
    byte uid[10];
    uint8_t uidlen;
}UID_t;

typedef struct {
    UID_t uid;
    uint32_t password;
}card_t;

typedef enum{
READ_OK,
NOTFOUND,
AUTH_ERROR,
CAN_NOT_READ_UID,
UID_LEN_ERROR,
READ_ERROR

}READER_status_t;

void Reader_Init();
void Reader_Sleep();
void Reader_WakeUp();
bool Reader_IsMifare();
READER_status_t Reader_ReadBlock();     
//void Reader_WriteBlock();
void Reader_Fill_List();
bool Reader_ComparePassword();     //kart bilgileri gösterilecek
void READER_stop();
bool READER_handler();
