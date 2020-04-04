#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__

#include "types.h"

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

typedef enum : u8
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

typedef enum : u8
{
    lst_SpecificHours = 0,
    lst_Immediately
} LogSendTimeType_t;

typedef enum : u8
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
    union LogSendDetails
    {
        char mailAddress[DEVICE_CFG_ADDR_LENGTH];
        char restAddress[DEVICE_CFG_ADDR_LENGTH];
        IP_Port udpAddress;
        char paidServiceToken[DEVICE_CFG_ADDR_LENGTH];
    };
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

#endif // __DEVICECONFIG_H__
