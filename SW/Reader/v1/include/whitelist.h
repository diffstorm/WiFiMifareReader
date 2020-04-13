#ifndef _whitelist_H_
#define _whitelist_H_

#include<stdint.h>
#include<Arduino.h>

typedef struct __attribute__((packed))
{
    byte uid[10];
    uint8_t length;
} whitelist_UID_t;

typedef struct __attribute__((packed))
{
whitelist_UID_t uid;
char name[10];
char surname[10];
} whitelist_t;

u16 CRC16(u16 crc, unsigned char *i, unsigned int l);
void WH_add(whitelist_t whl);
bool WH_delete(byte uid[],size_t len);
bool WH_searchUID(byte uid[],size_t len);

#endif