#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SSID_LEN_MAX          32
#define PSK_LEN_MAX           63
#define bool u8
#define IPAddress u32

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

typedef enum
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
    IPAddress ip;
    u16 port;
}
IP_Port;

#define DEVICE_CFG_NAME_LENGTH      32
#define DEVICE_CFG_ADDR_LENGTH      64
#define LOG_SPECIFIC_HOURS_COUNT    5
#define CARD_SCAN_RULES_COUNT       5
#define DOOR_SWITCH_COUNT           5

typedef struct __attribute__((packed))
{
    char company[DEVICE_CFG_NAME_LENGTH]; // null terminated
    char department[DEVICE_CFG_NAME_LENGTH];
    char deviceName[DEVICE_CFG_NAME_LENGTH];
    char deviceNote[DEVICE_CFG_NAME_LENGTH];
    char systemPwd[DEVICE_CFG_NAME_LENGTH];
    char webPwd[DEVICE_CFG_NAME_LENGTH];
    char mDNSName[DEVICE_CFG_NAME_LENGTH];
}
DeviceInfo_t;

typedef enum
{
    pt_In = 0,
    pt_Out
} PassingType_t;

typedef struct __attribute__((packed)) // Wifi profile
{
    char ssid[SSID_LEN_MAX];
    char psk[PSK_LEN_MAX];
    bool active : 8;
}
Conn_t;

typedef struct __attribute__((packed))
{
    Conn_t   wConnSTA;       // Connection parameters as station
    Conn_t   wConnAP;        // Connection parameters as access point
}
WiFiConfig_t;

typedef struct __attribute__((packed))
{
    char name[DEVICE_CFG_NAME_LENGTH]; // null terminated
    bool talkDirectly; // ESPNow or UDP
}
DoorSwitch_t;

typedef struct __attribute__((packed))
{
    u8 hour_begin;
    u8 hour_end;
    u8 dow;
    bool VisitorPass; // Can VISITOR card pass?
    bool GuardPass; // Can GUARD card pass?
}
DeviceRestrictions_t;

typedef enum
{
    lst_SpecificHours = 0,
    lst_Immediately
} LogSendTimeType_t;

typedef enum
{
    lsm_Mail = 0,
    lsm_REST,
    lsm_UDP,
    lsm_PaidService
} LogSendMethod_t;

typedef struct __attribute__((packed))
{
    bool active;
    LogSendTimeType_t logSendTimeType;
    u8 SpecificHours[LOG_SPECIFIC_HOURS_COUNT]; // < 24 for valid hour
    LogSendMethod_t logSendMethod;
    union
    {
        char mailAddress[DEVICE_CFG_ADDR_LENGTH];
        char restAddress[DEVICE_CFG_ADDR_LENGTH];
        IP_Port udpAddress;
        char paidServiceToken[DEVICE_CFG_ADDR_LENGTH];
    } LogSendDetails;
    bool LogUnauthorized;
    bool LogNewCards;
    bool LogRemovedCards;
    bool LogRestrictions;
    bool LogAdminActivities;
}
LogSettings_t;

typedef struct __attribute__((packed))
{
    u8 hour_begin; // < 24 for valid hour
    u8 hour_end; // < 24 for valid hour
    u16 period; // [ms]
}
CardScanRule_t;

typedef struct __attribute__((packed))
{
    CardScanRule_t cardScanRule[CARD_SCAN_RULES_COUNT];
    bool wakeCardActive;
    bool IRDetectActive;
    u8 AntennaPower;
    u8 RFCalibrationValue;
}
LowPowerMode_t;

typedef struct __attribute__((packed))
{
    bool AutoVersionCheck;
    u8 CheckPeriod;
}
FirmwareChecks_t;

typedef struct __attribute__((packed))
{
    DeviceInfo_t info;
    PassingType_t passingType;
    WiFiConfig_t wifiConfig;
    DoorSwitch_t doorSwitch[DOOR_SWITCH_COUNT];
    DeviceRestrictions_t restrictions;
    LogSettings_t logSettings;
    LowPowerMode_t lowPowerMode;
    FirmwareChecks_t firmwareChecks;
}
DeviceConfig_t;

// RLE Compress Encoder function
// param i : input buffer where the raw data come from
// param l : input buffer byte length
// param o : output buffer which will contaion compressed data
// return  : byte length of output buffer o
unsigned int rle_encode(unsigned char *i, int l, unsigned char *o)
{
    int b = 0, c = 0, x, j;
    unsigned char d;

    while(c < l)
    {
        x = c;
        d = i[x++];
        while(x < l && x - c < 127 && i[x] == d)
        {
            x++;
        }
        if(x - c == 1)
        {
            while(x < l && x - c < 127
                    && (i[x] != i[x - 1]
                        || (x > 1 && i[x] != i[x - 2])))
            {
                x++;
            }
            while(x < l && i[x] == i[x - 1])
            {
                x--;
            }
            o[b++] = (unsigned char)(c - x);
            for(j = c; j < x; j++)
            {
                o[b++] = i[j];
            }
        }
        else
        {
            o[b++] = (unsigned char)(x - c);
            o[b++] = d;
        }
        c = x;
    }
    return (b);
}

// RLE Compress Decoder function
// param i : input buffer contains previously compressed data
// param l : length of raw data used in encode function (not length of compressed input)
// param o : output buffer which will contain decompressed data
// return  : none
void rle_decode(unsigned char *i, int l, unsigned char *o)
{
    signed char c;

    while(l > 0)
    {
        c = (signed char) * i++;
        if(c > 0)
        {
            memset(o, *i++, c);
        }
        else if(c < 0)
        {
            c = (signed char) - c;
            memcpy(o, i, c);
            i += c;
        }
        o += c;
        l -= c;
    }
}

int main()
{
    static DeviceConfig_t dc, dc2;
    static u8 buffer[sizeof(DeviceConfig_t) + sizeof(DeviceConfig_t) / 127 + 1];
    static u16 outsize;
    static bool eq;

    outsize = rle_encode((u8 *)&dc, sizeof(dc), buffer);
    rle_decode(buffer, sizeof(dc), (u8 *)&dc2);

    eq = memcmp(&dc, &dc2, sizeof(dc));

    printf("DeviceConfig_t %lu\n", sizeof(DeviceConfig_t));
    printf("dc %lu\n", sizeof(dc));
    printf("buffer %lu\n", sizeof(buffer));
    printf("outsize %d\n", outsize);
    printf("eq %d\n", eq);

    return 0;
}

/*
Console output:

DeviceConfig_t 699
dc 699
buffer 705
outsize 12
eq 0
*/