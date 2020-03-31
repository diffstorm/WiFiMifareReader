#ifndef __TYPES_H__
#define __TYPES_H__

typedef enum // Device hardware model, look at DeviceConfig.h : DeviceModel definition
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
    u8 year;
    u8 hour;
    u8 minute;
    u8 second;
} DateTime_t;

typedef struct __attribute__((packed))
{
    u8 sunday : 1;
    u8 monday : 1;
    u8 tuesday : 1;
    u8 wednesday : 1;
    u8 thursday : 1;
    u8 friday : 1;
    u8 saturday : 1;
} DaysOfWeek_t;

typedef enum
{
    t_MS = 0,
    t_Seconds = 1,
    t_Minutes = 2,
    t_Hours = 3,
    t_Days = 4,
    t_Weeks = 5
} TimeUnit_t;

#endif // __TYPES_H__