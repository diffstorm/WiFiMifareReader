#ifndef __DEFS_H__
#define __DEFS_H__
#define RTC_MEMORY_BLOCK 4

#include <Arduino.h>


typedef struct
{
  byte junk01[32]; //may be constant
  byte section1[192];
  byte junk02[48]; //may be constant
  byte section2[96];
  byte junk03[16]; //may be constant
  byte section3[128];
} RTCMemory_t;

u16 RTC_CalcPadding(u16 size, u16 mult);

extern void RTC_Hexdump_Memory(char *desc, void *addr, int len);

extern  bool RTC_Write_Memory(int addr,void* data,u16 len);

extern bool RTC_Read_Memory(int addr,void* data,u16 len);



#endif