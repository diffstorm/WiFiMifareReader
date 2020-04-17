#ifndef __WHITELIST_H__
#define __WHITELIST_H__

#include<stdint.h>
#include<Arduino.h>
#include <LinkedList.h>
typedef struct __attribute__((packed))
{
    byte uid[10];
    uint8_t length;
}
whitelist_UID_t;

typedef struct __attribute__((packed))
{
    whitelist_UID_t uid;
    char name[20];
    char surname[20];
}
whitelist_t;

u16 CRC16(u16 crc, unsigned char *i, unsigned int l);
void WH_add(whitelist_t whl);
bool WH_delete(byte uid[], size_t len);
bool WH_searchUID(byte uid[], size_t len);
void WH_setFileName();
void WH_getFileName(u32 pos);
#endif