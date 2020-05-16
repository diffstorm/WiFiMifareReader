#include <NTPClient.h>
#include <WiFiUdp.h>

#define gmtOffset_sec  3*3600

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

bool NTP_get_time(u64 *epoch)
{
    bool ret = false;

    timeClient.begin();
    timeClient.setTimeOffset(gmtOffset_sec);

    if(false != timeClient.update())
    {
        *epoch = timeClient.getEpochTime() * 1000; // TODO rtc ye yazılacak
        timeClient.end();
        ret = true;
    }

    return ret;
}