#ifndef __CARDCONFIG_H__
#define __CARDCONFIG_H__

#include "types.h"

#define CARD_CFG_NAME_LENGTH 32
#define CARD_ROW_SIZE        16 // # of bytes in a sector
#define CARD_SECTOR_SIZE     48 // # of sectors in a card
#define CARD_MAX_SIZE        (CARD_ROW_SIZE * CARD_SECTOR_SIZE)
#define CARD_CHECKSUM_SEED   0xDEAD

typedef enum : u8
{
    ct_IDLE = 0,
    ct_UNUSED,
    ct_VISITOR,
    ct_GUARD,
    ct_USER,
    ct_ADMIN,
    ct_SERVICE,
    ct_WAKE,
    ct_MAX
} CardType_t;

typedef struct __attribute__((packed))
{
    u8 uid[10];
    u8 length;
}
UID_t;

typedef struct __attribute__((packed))
{
    Version_t version;
    CardType_t type;
    time_t record_date;
    UID_t uid;
}
CardInfo_t;

typedef struct __attribute__((packed))
{
    char id[CARD_CFG_NAME_LENGTH]; // null terminated
    char name[CARD_CFG_NAME_LENGTH];
    char surname[CARD_CFG_NAME_LENGTH];
    char mail[CARD_CFG_NAME_LENGTH];
    char company[CARD_CFG_NAME_LENGTH];
    char department[CARD_CFG_NAME_LENGTH];
}
CardPersonal_t;

typedef struct __attribute__((packed))
{
    u8 hour_begin; // not zero for valid hour
    u8 hour_end; // not zero for valid hour
    u8 dow;
    time_t validuntil;
}
CardRestrictions_t;

typedef struct __attribute__((packed))
{
    CardInfo_t info;
    CardPersonal_t personal;
    CardRestrictions_t restrictions;
}
card_t;

typedef struct
{
    u16 checksum;
    u16 length;
    u16 random;
    u16 bcc;
    u8 *data;
} cardRaw_t;

#endif // __CARDCONFIG_H__