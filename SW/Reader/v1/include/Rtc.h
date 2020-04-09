#ifndef __DEFS_H__
#define __DEFS_H__
#define RTC_MEMORY_BLOCK 4
#define RTC_USER_DATA_ADDR 66   //kullanıcının RTC memory'e yazacağı datalar 65 ile 110 numaralı adresler arasında olacaktır.
#define RTC_TIME_MEMORY 120     //epoch time bilgisi 110 numaralı adresten itibaren yazılacak

#include <Arduino.h>


typedef struct __attribute__((packed))
{
  uint32_t user_data;
} RTCMemory_t;


typedef struct __attribute__((packed))
{
  unsigned long epocTime;
}RTC_time_t;


u16 RTC_CalcPadding(u16 size, u16 mult);

extern  bool RTC_Write_Memory(RTCMemory_t* data,u16 len);

extern bool RTC_Read_Memory(RTCMemory_t* data,u16 len); 

extern bool RTC_Write_Time_Memory(RTCMemory_t* data,u16 len); 

extern bool RTC_Read_Time_Memory(RTCMemory_t* data,u16 len); 

#endif