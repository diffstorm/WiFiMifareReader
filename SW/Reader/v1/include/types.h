#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "defs.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef enum // Device hardware model, look at defs.h : DeviceModel definition
{
    mWiFiReader = 0,
    mWiFiRelay,
    mRFReader,
    mRFButton,
    mRFBuzzer
} HWModel_t;

typedef struct
{
    u8 minor;
    u8 major;
} Version_t;

typedef struct
{
    u8 day;
    u8 month;
    u16 year;
    u8 hour;
    u8 minute;
    u8 second;
} DateTime_t;

typedef enum : u8
{
    Sunday      = 1,
    Monday      = 2,
    Tuesday     = 4,
    Wednesday   = 8,
    Thursday    = 16,
    Friday      = 32,
    Saturday    = 64
} Days_t;

typedef enum
{
    t_MS = 0,
    t_Seconds = 1,
    t_Minutes = 2,
    t_Hours = 3,
    t_Days = 4,
    t_Weeks = 5
} TimeUnit_t;

typedef struct __attribute__((packed))
{
    u32 ip; // IPAddress
    u16 port;
}
IP_Port;

#endif // __TYPES_H__