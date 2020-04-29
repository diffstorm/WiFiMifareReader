#include "Device.h"
#include "tools.h"

// TODO : add ntp settings

bool Device_SetInfo(DeviceConfig_t *device, char *company, char *department, char *deviceName, char *deviceNote, char *systemPwd, char *webPwd, char *mDNSName)
{
    bool ret = true;

    if(0 == strnlen(deviceName, DEVICE_CFG_NAME_LENGTH))
    {
        ret = false;
    }
    if(0 == strnlen(systemPwd, DEVICE_CFG_NAME_LENGTH))
    {
        ret = false;
    }
    if(false != ret)
    {
        strncpy(device->info.company, company, DEVICE_CFG_NAME_LENGTH);
        strncpy(device->info.department, department, DEVICE_CFG_NAME_LENGTH);
        strncpy(device->info.deviceName, deviceName, DEVICE_CFG_NAME_LENGTH);
        strncpy(device->info.deviceNote, deviceNote, DEVICE_CFG_NAME_LENGTH);
        strncpy(device->info.systemPwd, systemPwd, DEVICE_CFG_NAME_LENGTH);
        strncpy(device->info.webPwd, webPwd, DEVICE_CFG_NAME_LENGTH);
        strncpy(device->info.mDNSName, mDNSName, DEVICE_CFG_NAME_LENGTH);
    }

    return ret;
}

bool Device_SetPassingType(DeviceConfig_t *device, PassingType_t pt)
{
    bool ret = false;
    if(pt < pt_MAX)
    {
        device->passingType = pt;
        ret = true;
    }
    return ret;
}

WiFiProfileSTA_t Device_CreateWiFiProfileSTA(bool active, u8 bssid[6], bool bssid_active, char *ssid, char *psk, bool dhcp, u32 ip, u32 subnet, u32 gateway, u32 dns, u32 dns2)
{
    WiFiProfileSTA_t ret;

    memset(&ret, 0, sizeof(WiFiProfileSTA_t));
    ret.active = active;
    ret.bssid_active = bssid_active;
    if(bssid_active)
    {
        memcpy(ret.bssid, bssid, sizeof(bssid));
    }
    strncpy(ret.ssid, ssid, SSID_LEN_MAX);
    strncpy(ret.psk, psk, SSID_LEN_MAX);
    ret.dhcp = dhcp;
    ret.ip = ip;
    ret.subnet = subnet;
    ret.gateway = gateway;
    ret.dns = dns;
    ret.dns2 = dns2;

    return ret;
}

WiFiProfileAP_t Device_CreateWiFiProfileAP(bool active, char *ssid, char *psk, u32 ip, u32 subnet, bool ssid_hidden, u8 channel)
{
    WiFiProfileAP_t ret;

    memset(&ret, 0, sizeof(WiFiProfileAP_t));
    ret.active = active;
    strncpy(ret.ssid, ssid, SSID_LEN_MAX);
    strncpy(ret.psk, psk, SSID_LEN_MAX);
    ret.ip = ip;
    ret.subnet = subnet;
    ret.ssid_hidden = ssid_hidden;
    if(14 > channel)
    {
        ret.channel = channel;
    }

    return ret;
}

bool Device_SetWifiConfig(DeviceConfig_t *device, WiFiProfileSTA_t STA, WiFiProfileAP_t AP)
{
    bool ret = true;
    size_t size;

    if(false == STA.active && false == AP.active)
    {
        ret = false;
    }
    if(false != ret && false != STA.active)
    {
        size = strnlen(STA.psk, PSK_LEN_MAX);
        if((strnlen(STA.ssid, SSID_LEN_MAX) == 0) || (size > 0 && size < 8) || (false == STA.dhcp && (0 == STA.ip || 0 == STA.subnet)))
        {
            ret = false;
        }
        if(false == STA.bssid_active)
        {
            memset(STA.bssid, 0, sizeof(STA.bssid));
        }
        if(false == STA.dhcp)
        {
            STA.ip = 0;
            STA.subnet = 0;
            STA.gateway = 0;
        }
        if(0 == STA.dns)
        {
            STA.dns2 = 0;
        }
    }
    if(false != ret && false != AP.active)
    {
        size = strnlen(AP.psk, PSK_LEN_MAX);
        if(strnlen(AP.ssid, SSID_LEN_MAX) == 0 || (size > 0 && size < 8))
        {
            ret = false;
        }
        if(0 == AP.ip)
        {
            AP.subnet = 0;
        }
    }
    if(false != ret)
    {
        device->wifiConfig.STA = STA;
        device->wifiConfig.AP = AP;
    }

    return ret;
}

void Device_SetDoorSwitch(DeviceConfig_t *device, DoorSwitch_t ds, u8 index)
{
    if(DOOR_SWITCH_COUNT > index)
    {
        device->doorSwitch[index] = ds;
    }
}

void Device_SetNoDoorSwitch(DeviceConfig_t *device)
{
    u16 i;

    for(i = 0; i < DOOR_SWITCH_COUNT; i++)
    {
        memset(&device->doorSwitch[i], 0, sizeof(DoorSwitch_t));
    }
}

u16 Device_GetDoorSwitchCount(DeviceConfig_t *device)
{
    u16 ret = 0;
    u16 i;

    for(i = 0; i < DOOR_SWITCH_COUNT; i++)
    {
        if(cc_Disabled < device->doorSwitch[i].commChannel && cc_MAX > device->doorSwitch[i].commChannel && 0 < strlen(device->doorSwitch[i].name))
        {
            ret++;
        }
    }

    return ret;
}

//! \example : Device_SetRestrictions(&device, 8, 19, Saturday | Sunday, true, false);
void Device_SetRestrictions(DeviceConfig_t *device, u8 begin, u8 end, u8 dow, bool visitor, bool guard)
{
    device->restrictions.hour_begin = begin;
    device->restrictions.hour_end = end;
    device->restrictions.dow = dow;
    device->restrictions.Visitor = visitor;
    device->restrictions.Guard = guard;
}

void Device_SetNoRestrictions(DeviceConfig_t *device)
{
    memset(&device->restrictions, 0, sizeof(DeviceRestrictions_t));
}

bool Device_isRestricted(DeviceConfig_t *device, u8 hour, Days_t today, CardType_t type)
{
    bool ret = false;

    if(24 > hour && 0 < device->restrictions.hour_begin && 0 < device->restrictions.hour_end)
    {
        if(device->restrictions.hour_begin < device->restrictions.hour_end)
        {
            ret = hour >= device->restrictions.hour_begin && hour <= device->restrictions.hour_end;
        }
        else
        {
            ret = hour >= device->restrictions.hour_begin || hour <= device->restrictions.hour_end;
        }
    }

    if(0 < today && (device->restrictions.dow & today))
    {
        ret = true;
    }

    if(false != device->restrictions.Visitor && ct_VISITOR == type)
    {
        ret = true;
    }

    if(false != device->restrictions.Guard && ct_GUARD == type)
    {
        ret = true;
    }

    return ret;
}

void Device_SetLogSettings(DeviceConfig_t *device)
{
    // TODO: @Cihan
}

void Device_SetNoLog(DeviceConfig_t *device)
{
    memset(&device->logSettings, 0, sizeof(LogSettings_t));
}

void Device_SetLowPowerMode(DeviceConfig_t *device)
{
    // TODO:
}

void Device_SetNoLowPowerMode(DeviceConfig_t *device)
{
    memset(&device->lowPowerMode, 0, sizeof(LowPowerMode_t));
}

void Device_SetFirmwareChecks(DeviceConfig_t *device, bool AutoVersionCheck, u8 CheckPeriod)
{
    device->firmwareChecks.AutoVersionCheck = AutoVersionCheck;
    device->firmwareChecks.CheckPeriod = CheckPeriod;
}

void Device_SetNoFirmwareChecks(DeviceConfig_t *device)
{
    memset(&device->firmwareChecks, 0, sizeof(FirmwareChecks_t));
}

void Device_SetDefault(DeviceConfig_t *device)
{
    char name[SSID_LEN_MAX];

    snprintf(name, SSID_LEN_MAX, SSID_NAME_PATTERN, DeviceName, DeviceChipID);
    memset(device, 0, sizeof(DeviceConfig_t));
    Device_SetInfo(device, NULL, NULL, name, NULL, (char *)DevicePassword, NULL, NULL);
    Device_SetPassingType(device, pt_In);
    WiFiProfileSTA_t STA = Device_CreateWiFiProfileSTA(false, NULL, false, NULL, NULL, false, 0, 0, 0, 0, 0);
    WiFiProfileAP_t AP = Device_CreateWiFiProfileAP(true, name, (char *)DevicePassword, 0, 0, false, 0);
    Device_SetWifiConfig(device, STA, AP);
    Device_SetNoDoorSwitch(device);
    Device_SetNoRestrictions(device);
    Device_SetNoLog(device);
    Device_SetNoLowPowerMode(device);
    Device_SetNoFirmwareChecks(device);
}
