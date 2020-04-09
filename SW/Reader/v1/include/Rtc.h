#ifndef __DEFS_H__
#define __DEFS_H__
#define RTC_MEMORY_BLOCK 4
#define RTC_USER_DATA_ADDR 66

#include <Arduino.h>


typedef struct
{
  uint32_t user_data;
} RTCMemory_t;

u16 RTC_CalcPadding(u16 size, u16 mult);

extern  bool RTC_Write_Memory(RTCMemory_t* data,u16 len);

extern bool RTC_Read_Memory(RTCMemory_t* data,u16 len); 

#endif