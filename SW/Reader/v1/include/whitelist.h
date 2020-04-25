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
bool WL_updateFile(char *name, char *name2, void *context, u32 length, u32 pos);
void WL_add(whitelist_t whl);
bool WL_delete(byte uid[], size_t len);
long WL_searchUID(byte uid[], size_t len);
void WL_setFileName(char* filename, char* filename2);
void WL_getFileName(u32 pos, char* filename, char* filename2);
void WL_getLastFileName(char* filename, char* filename2);
#endif