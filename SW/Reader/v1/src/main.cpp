#include <ESP8266WiFi.h>
#include <FS.h>
#include "Reader.h"
#include "Buzzer.h"
#include "IR.h"
#include "tools.h"
#include "FileSystem.h"
#include "whitelist.h"
#include "UDPserver.h"
#include "NTP.h"

extern "C" {
#include "user_interface.h"
#include <espnow.h>
}

RF_PRE_INIT()
{
    system_phy_set_powerup_option(31);  // Do full RF calibration on power-up
    system_phy_set_max_tpw(82);         // Set max TX power
}

inline void SetupBoard()
{
    pinMode(15, OUTPUT);
}
PR_Packet_t item;
char ip[] = "192.168.1.35";
IPAddress remote_addr;
ESP8266WiFiClass Wifi;
void setup()
{


#ifdef WDT
    ESP.wdtDisable();
    ESP.wdtEnable(WDTO_8S);
#endif
#ifdef SERIAL_PORT
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.flush();
#endif
    LOG_Init(115200);
    Reader_Init();
#ifdef IR_CARD_DETECT
    IR_Init();
#endif
    BZR_Init();
#ifdef SERIAL_PORT
    WiFi.printDiag(Serial);
    system_show_malloc();
#endif
    //LOGp("Testing %d and %f also %s", 123, 12.3, "this");
    UDPinit();


////////////////////////////////////////////////////////////////////

    item.buffer = (unsigned char *)(malloc(6));
    byte x[] = {0xAA, 0xBB, 0xAA, 0xAA, 0xAA};
    for(int i = 0; i < 6; i++)
    {
        item.buffer[i] = x[i];
    }
    Wifi.hostByName(ip, remote_addr);
    item.ip = (IPAddress *)(malloc(sizeof(remote_addr)));
    memcpy(item.ip, &remote_addr, sizeof(remote_addr));
    item.length = 6;
    item.port = 55131;
///////////////////////////////////////////////////////////////////////
}
bool status = false;
void loop()
{
    PR_Packet_t *itemmptr;
    PR_Packet_t itemm;
    itemmptr = &itemm;
    UDP_recieve(itemmptr);
    if(false == status)
    {
        u64 *epoch;
        u64 eepoch;
        epoch = &eepoch;

        PR_Packet_t *itemmmm;
        itemmmm = &item;
        NTP_get_time(epoch);
        UDP_send(itemmmm);
        //send_example();
        status = true;
    }

    //Serial.printf("%s\n", itemptr->devicename);
    //Serial.printf("id : %d",itemptr->id);
//example_udp();

}

