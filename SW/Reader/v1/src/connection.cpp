#include<connection.h>

const char* ssid="PAYCORE_VINN";
const char* password="Oneclick2019";
unsigned int localPort=2000;
WiFiUDP udp;

IPAddress ServerIP(192,168,4,1);
IPAddress ClientIP(192,168,4,2);

char packetBuffer[9];

void ESP_Wifi_Init()
{
    WiFi.softAP(ssid,password);
    udp.begin(localPort);
}

void ESP_WiFi_Handler()
{
    
}