#ifndef __DEFS_H__
#define __DEFS_H__

#include <ESP8266WiFi.h>

// Code Modules Settings
// ------------------------------------------
//#define DEVELOPER_MODE    // uncomment on production
#define WDT                 // Watch dog timer
//#define SERIAL_PORT
//#define IR_CARD_DETECT
//#define LOW_POWER_MODE
//#define ESP_NOW
//#define UDP_SERVER
#define WEB_SERVER          // Web server for device control
#define OTA_HTTPCLIENT      // /ota downloads .bin file from http and upgrades the firmware
#define OTA_HTTPSERVER      // /update has an upload form for the local .bin file
// ------------------------------------------

// Communication Layer Definitions
// ------------------------------------------
#define UDP_DISCOVERY_PORT    35033
#define WEB_SERVER_PORT       80
// ------------------------------------------

// Device Definitions
// ------------------------------------------
#define FW_VersionMajor		  1
#define FW_VersionMinor		  0
#define DeviceModel			  mWiFiReader
#define DeviceChipID		  ESP.getChipId()
#define DeviceFlashID		  ESP.getFlashChipId()
#define FS_ROOTDIR	          "/"
#define DEVICE_CONFIG_MAGIC_NUMBER   0x0001
#define FS_DEVICE_CONFIG_NAME    "/dc.cf"
#define SSID_NAME_PATTERN     "%s_%06x" // name generation pattern for snprintf
#define SSID_LEN_MAX          WL_SSID_MAX_LENGTH
#define PSK_LEN_MAX           WL_WPA_KEY_MAX_LENGTH
#define VERSION_WEB_ADDRESS   "http://usr:pwd@private.karttasarimi.com/ota/wmrv.txt"
#define OTA_WEB_ADDRESS       "http://usr:pwd@private.karttasarimi.com/ota/wmr.bin"

#define COMM_HANDLE_PERIOD     20 // [ms]
#define WIFI_HANDLE_PERIOD     5 // [sec]
#define WEB_HANDLE_PERIOD      150 // [ms]

#define RSSI_AMAZING		  (-30)
#define RSSI_GREAT			  (-67)
#define RSSI_ENOUGH			  (-70)
#define RSSI_BAD			  (-80)
#define RSSI_USELESS		  (-90)
// ------------------------------------------

// Hardware pin definitions
// ------------------------------------------
//TODO:
// ------------------------------------------

// Macros
// ------------------------------------------
#define Low(c)          (*(unsigned char*)&(c))
#define High(c)         (*((unsigned char*)&(c)+1))
#define GET8(x,n)       ((x>>(n*8)&0xFF))
#define MAKE16(x,y)     (((((u16)x)<<8))|((u16)y))
#define MAKE32(w,x,y,z) (((((u32)w)<<24))|((((u32)x)<<16))|((((u32)y)<<8))|((u32)z))
#define ISBIGENDIAN()	  (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) ? true : false
#ifndef max
#define max(a,b)        (((a) > (b)) ? (a) : (b))
#endif
// ------------------------------------------

#endif // __DEFS_H__