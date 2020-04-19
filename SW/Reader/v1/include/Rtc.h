#ifndef __RTC_H__
#define __RTC_H__

#define RTC_USER_ADDR 65

#include "types.h"

typedef struct __attribute__((packed))
{
  u64 utc;
  u32 startvalue;
} UTC_t;

typedef enum : u8
{
  RTC_idle = 0,
  RTC_NoTime,
  RTC_ValidTime,
  RTC_MAX
} RTC_Status_t;

typedef struct __attribute__((packed))
{
  UTC_t time;
  u16 checksum;
} RTC_Memory_t;

extern u64 RTC_GetTime();
extern u32 RTC_GetEpoch();
extern void RTC_SetEpoch(u32 epoch);

extern bool RTC_StoreTime(UTC_t utc);
extern void RTC_Init();
extern void RTC_Handler();

#endif // __RTC_H__