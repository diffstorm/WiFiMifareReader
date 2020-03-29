#include <MFRC522.h>
#include <SPI.h>
#include <LinkedList.h>

typedef struct
{
    byte uid[10];
    uint8_t uidlen;
} UID_t;

typedef struct
{
    UID_t uid;
    int32_t password;
} card_t;

//------------------------------
/*
#define NAME_LENGTH 32

typedef struct
{
    u8 minor;
    u8 major;
    u8 build;
} Version_t;

typedef enum
{
    ct_IDLE = 0,
    ct_UNUSED,
    ct_VISITOR,
    ct_GUARD,
    ct_USER,
    ct_ADMIN,
    ct_WAKE,
    ct_END
} CardType_t;

typedef struct
{
    u8 day;
    u8 month;
    u8 year;
    u8 hour;
    u8 minute;
    u8 second;
} DateTime_t;

typedef struct __attribute(packed)
{
    u8 sunday : 1;
    u8 monday : 1;
    u8 tuesday : 1;
    u8 wednesday : 1;
    u8 thursday : 1;
    u8 friday : 1;
    u8 saturday : 1;
} DaysOfWeek_t;

typedef struct
{
    UID_t uid;
    Version_t version;
    CardType_t type;
    u32 hash;
} card_info_t;

typedef struct
{
    DateTime_t record_date;
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];
    u32 id;
    char mail[NAME_LENGTH]; // null terminated
    char company[NAME_LENGTH];
    char department[NAME_LENGTH];
} card_permanent_sector_t;

typedef struct
{
    u8 hour_begin;
    u8 hour_end;
    DaysOfWeek_t dow;
} card_restrictions_sector_t;

typedef struct
{
    DateTime_t record_date;
    u32 pass_count;
} card_volatile_sector_t;

typedef struct
{
    u32 hash_permanent;
    u32 hash_volatile;
    u32 hash_restrictions;
} card_hash_sector_t;

typedef struct
{
    card_info_t info;
    card_permanent_sector_t permanent;
    card_volatile_sector_t volatile;
    card_restrictions_sector_t restrictions;
    card_hash_sector_t hash;
} card2_t;

typedef struct
{
    u32 length;
    u8 data[CARD_MAX_SIZE];
} encrypted_card_t;

void kart_yaz(card2_t *card)
{
    encrypted_card_t ec2;
    encrypted_card_t ec = şifrele(card);
    yaz(ec);
    oku(&ec2);
    if(0 == memcmp(ec2, ec, sizeof(encrypted_card_t))
    {
        return true;
    }
    return false;
}

void kart_oku(card2_t *card)
{
    oku(card);
    şifreçöz(card);
    return hash_kontrol(card);
}

*/
//------------------------------

typedef enum
{
    READ_OK,
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
READER_status_t Reader_ReadBlock();
//void Reader_WriteBlock();
void Reader_Fill_List();
bool Reader_ComparePassword();     //kart bilgileri gösterilecek
void READER_stop();
bool READER_handler();
