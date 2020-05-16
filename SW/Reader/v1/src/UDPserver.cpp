#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <UDPserver.h>
#include "DebugLog.h"
#include<LinkedList.h>
#define MAX_QUEUE_SIZE 250

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  //defs.h tan mı alınacak
const char *ssid = "saseylisalasula";
const char *password = "Biradetsifre35";

LinkedList<PR_Packet_t> UDP_message_queue = LinkedList<PR_Packet_t>();

bool UDPinit()  //wifi bölümü deneme amaçlı yazıldı. Wifi tarafı yazılınca burada kontrol edilecek
{
    bool ret = false;
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected");
    if(1 == Udp.begin(localUdpPort))
    {
        ret = true;
    }
    return ret;
}

bool UDP_write(u8 *str, u32 length)
{
    u32 offset = 0;
    u32 written = 0;
    u8 error = 3;

    while(offset < length && error > 0)
    {

        written =  Udp.write(str + offset, length);

        if(written > 0)
        {
            offset += written;
        }
        else
        {
            error--;
        }
    }
    Serial.println(offset == length);
    return offset == length;
}

bool UDP_read(u8 *str, u32 length)
{
    u32 offset = 0;
    u32 read = 0;
    u8 error = 3;

    while(offset < length && error > 0)
    {
        read =  Udp.read((str + offset), length);
        if(read > 0)
        {
            offset += read;
        }
        else
        {
            error--;
        }
    }
    return offset == length;
}

bool UDP_send(PR_Packet_t *item)
{
    bool ret = false;

    if(1 == Udp.beginPacket(*(item->ip), item->port))
    {
        Serial.println(*(item->ip));
        Serial.println(item->port);
        if(false != UDP_write(item->buffer, item->length))
        {   
            LOGh("item buffer: ", item->buffer);
            if(1 == Udp.endPacket())
            {
                ret = true;
            }
        }

    }

    return ret;
}


/*
00 AA LH LL LCRC DATA[LEN] CRCH CRCL

LCRC -> CRC([LH, LL], 2) -> 2 byte -> LCRCH^LCRCL
*/
void UDP_recieve(PR_Packet_t *item)
{

    int packetSize = Udp.parsePacket();

    /*while(0 < packetSize)
    {

        if(0x00 == Udp.read() && 0 < packetSize)
        {
            LOG("00 tuttu");
            packetSize--;
            if(0xAA == Udp.read())
            {
                packetSize--;
                LOG("AA tuttu");
                break;
            }
        }
    }*/

    if(0 < packetSize)
    {

        u8 *p;
        p = (u8 *)malloc(packetSize);

        if(NULL != p)
        {

            if(false != UDP_read(p, packetSize))
            {
                memcpy(item, p, packetSize);
                LOGh("buffer", &item->buffer);
                LOGh("pointer", p);
            }
            free(p);
        }


        else
        {
            LOG("memory allocation error");
        }
    }

}


bool UDP_fill_message_queue(PR_Packet_t item)
{
    bool ret = true;

    if(false == UDP_message_queue.add(item))
    {
        ret = false;
    }

    return ret;
}

