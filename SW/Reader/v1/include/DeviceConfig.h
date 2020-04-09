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
    pt_Out,
    pt_MAX
}
PassingType_t;

typedef struct __attribute__((packed)) // Wifi profile
{
    bool active : 8;
    u8 bssid[6]; // (STA)
    bool bssid_active;
    char ssid[SSID_LEN_MAX];
    char psk[PSK_LEN_MAX];
    bool dhcp : 8; // (STA)
    u32 ip;     // 192.168.1.100 (AP, STA)
    u32 subnet; // 255.255.255.1 (AP, STA)
    u32 gateway;// 192.168.1.1   (STA)
    u32 dns;    // 156.154.70.22 (STA)
    u32 dns2;   // 156.154.71.22 (STA)
}
WiFiProfile_t;

typedef struct __attribute__((packed))
{
    WiFiProfile_t STA;       // Connection parameters as station
    WiFiProfile_t AP;        // Connection parameters as access point
}
WiFiConfig_t;

typedef struct __attribute__((packed))
{
    char addr[DEVICE_CFG_ADDR_LENGTH]; // pool.ntp.org
    char addr2[DEVICE_CFG_ADDR_LENGTH];
    char addr3[DEVICE_CFG_ADDR_LENGTH];
    u32 ip;
    u16 port;
    u8 period; // [hours]
    int8_t timezone; // [hours] - Turkey UTC+03:00
}
NTPSettings_t;

typedef enum : u8
{
    cc_Disabled = 0,
    cc_UDP,
    cc_ESPNow,
    cc_MAX
}
CommChannel_t;

typedef struct __attribute__((packed))
{
    char name[DEVICE_CFG_NAME_LENGTH]; // null terminated
    CommChannel_t commChannel;
}
DoorSwitch_t;

typedef struct __attribute__((packed))
{
    u8 hour_begin;
    u8 hour_end;
    u8 dow;
    bool Visitor; // VISITOR card restricted?
    bool Guard; // GUARD card restricted?
}
DeviceRestrictions_t;

typedef enum : u8
{
    lst_SpecificHours = 0,
    lst_Immediately,
    lst_MAX
}
LogSendTimeType_t;

typedef enum : u8
{
    lsm_Mail = 0,
    lsm_REST,
    lsm_UDP,
    lsm_PaidService,
    lsm_MAX
}
LogSendMethod_t;

typedef struct __attribute__((packed))
{
    bool active;
    LogSendTimeType_t logSendTimeType;
    u8 SpecificHours[LOG_SPECIFIC_HOURS_COUNT]; // not zero for valid hour
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
    u8 hour_begin; // not zero for valid hour
    u8 hour_end; // not zero for valid hour
    u16 period; // [ms]
}
CardScanRule_t;

typedef struct __attribute__((packed))
{
    bool active;
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
    u8 CheckPeriod; // # of days
}
FirmwareChecks_t;

typedef struct __attribute__((packed))
{
    DeviceInfo_t info;
    PassingType_t passingType;
    WiFiConfig_t wifiConfig;
    NTPSettings_t ntpSettings;
    DoorSwitch_t doorSwitch[DOOR_SWITCH_COUNT];
    DeviceRestrictions_t restrictions;
    LogSettings_t logSettings;
    LowPowerMode_t lowPowerMode;
    FirmwareChecks_t firmwareChecks;
}
DeviceConfig_t;

#endif // __DEVICECONFIG_H__
