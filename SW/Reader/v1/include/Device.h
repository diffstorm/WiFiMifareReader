#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "DeviceConfig.h"
#include "CardConfig.h"

extern bool Device_SetInfo(DeviceConfig_t *device, char *company, char *department, char *deviceName, char *deviceNote, char *systemPwd, char *webPwd, char *mDNSName);

extern bool Device_SetPassingType(DeviceConfig_t *device, PassingType_t pt);

extern WiFiProfileSTA_t Device_CreateWiFiProfileSTA(bool active, u8 bssid[6], bool bssid_active, char *ssid, char *psk, bool dhcp, u32 ip, u32 subnet, u32 gateway, u32 dns, u32 dns2);
extern WiFiProfileAP_t Device_CreateWiFiProfileAP(bool active, char *ssid, char *psk, u32 ip, u32 subnet, bool ssid_hidden, u8 channel);
extern bool Device_SetWifiConfig(DeviceConfig_t *device, WiFiProfileSTA_t STA, WiFiProfileAP_t AP);

extern void Device_SetDoorSwitch(DeviceConfig_t *device, DoorSwitch_t ds, u8 index);
extern void Device_SetNoDoorSwitch(DeviceConfig_t *device);
extern u16 Device_GetDoorSwitchCount(DeviceConfig_t *device);

//! \example : Device_SetRestrictions(&device, 8, 19, Saturday | Sunday, true, false);
extern void Device_SetRestrictions(DeviceConfig_t *device, u8 begin, u8 end, u8 dow, bool visitor, bool guard);
extern void Device_SetNoRestrictions(DeviceConfig_t *device);
extern bool Device_isRestricted(DeviceConfig_t *device, u8 hour, Days_t today, CardType_t type);

//extern void Device_SetLogSettings(DeviceConfig_t *device);
extern void Device_SetNoLog(DeviceConfig_t *device);

//extern void Device_SetLowPowerMode(DeviceConfig_t *device);
extern void Device_SetNoLowPowerMode(DeviceConfig_t *device);

extern void Device_SetFirmwareChecks(DeviceConfig_t *device, bool AutoVersionCheck, u8 CheckPeriod);
extern void Device_SetNoFirmwareChecks(DeviceConfig_t *device);

extern void Device_SetDefault(DeviceConfig_t *device);

#endif // __DEVICE_H__