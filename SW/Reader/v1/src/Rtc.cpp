#include <Rtc.h>
#include <Schedule.h>
extern "C"
{
#include "user_interface.h"
}

unsigned long epochRTC;

u16 RTC_CalcPadding(u16 size, u16 mult)
{
  u16 padding = size % mult;
  if (padding > 0)
  {
    padding = mult - padding;
  }
  return padding;
}

void RTC_Hexdump_Memory(char *desc, void *addr, int len)
{
  int i;
  unsigned char buff[17];
  unsigned char *pc = (unsigned char *)addr;

  if (desc != NULL)
    Serial.printf("%s:\n", desc);

  if (len == 0)
  {
    Serial.printf("  ZERO LENGTH\n");
    return;
  }
  if (len < 0)
  {
    Serial.printf("  NEGATIVE LENGTH: %i\n", len);
    return;
  }

  for (i = 0; i < len; i++)
  {

    if ((i % 16) == 0)
    {

      if (i != 0)
        Serial.printf("  %s\n", buff);

      Serial.printf("  %04x ", i);
    }

    Serial.printf(" %02x", pc[i]);

    if ((pc[i] < 0x20) || (pc[i] > 0x7e))
      buff[i % 16] = '.';
    else
      buff[i % 16] = pc[i];
    buff[(i % 16) + 1] = '\0';
  }

  while ((i % 16) != 0)
  {
    Serial.printf("   ");
    i++;
  }

  Serial.printf("  %s\n", buff);
}

RTC_status_t RTC_Write_Memory(RTCMemory_t *data, u16 len)
{
  RTC_status_t status = WRITE_ERROR;
  u16 padding = RTC_CalcPadding(len, RTC_MEMORY_BLOCK);
  len += padding;
  if (512 < len)
  {
    Serial.printf("yeterli hafiza kalmamistir\n");
  }
  else
  {
    if (0 != system_rtc_mem_write(RTC_USER_DATA_ADDR, data, len))
    {
      yield();
      status = WRITE_OK;
    }
  }
  return status;
}

RTC_status_t RTC_Read_Memory(RTCMemory_t *data, u16 len)
{
  RTC_status_t status  = READ_ERROR;
  u16 padding = RTC_CalcPadding(len, RTC_MEMORY_BLOCK);
  len += padding;
  if (0 != system_rtc_mem_read(RTC_USER_DATA_ADDR, data, len))
  {
    yield();
    status = READ_OK;
  }
  return status;
}


RTC_status_t RTC_Update_Time_Memory()
{
  RTC_status_t status = UPDATE_ERROR;
  unsigned long epochRTC;
  if(0 != system_rtc_mem_write(RTC_TIME_MEMORY,&epochRTC, sizeof(epochRTC)))
  {
    epochRTC++;
    status = WRITE_OK;
    if(0 !=  system_rtc_mem_read(RTC_TIME_MEMORY, &epochRTC, sizeof(epochRTC)))
    {
      status = READ_OK;
    }
     status = UPDATE_OK;
  }
  return status;
}


/* 
#define RTC_UTC_ADDR 65
#define RTC_UTC_MILISECOND_ADDR 100

const long utcOffsetInSeconds = 3600*3;

void updateEpochTimeFromRTC();
void epochMillisRTC();

Ticker timer1(epochMillisRTC,1,0,MILLIS);
Ticker timer2(updateEpochTimeFromRTC,10,0 ,MILLIS);

unsigned long epochRTC = 1586969413;
unsigned long epocMillishRTC = 0;



bool RTC_Write_Memory(uint16_t address,unsigned long* data,size_t len)
{
  bool ret = false;

  if (512 < len)
  {
    Serial.printf("yeterli hafiza kalmamistir\n");
  }
  else
  {
    if (0 != system_rtc_mem_write(address, data, len))
    {
      yield();
      ret = true;
    }
  }
  return ret;
}

bool RTC_Read_Memory(uint16_t address,unsigned long* data,size_t len)
{
  bool ret = false;
  if (0 != system_rtc_mem_read(address, data, len))
  {
    yield();
    ret = true;
  }
  return ret;
}



void updateEpochTimeFromRTC()
{
  RTC_Write_Memory(RTC_UTC_ADDR,&epochRTC,sizeof(epochRTC));
  if((epocMillishRTC / 1000) > 0)
  {
    epochRTC += epocMillishRTC/1000;
    epocMillishRTC= epocMillishRTC % 1000;                   
    RTC_Write_Memory(RTC_UTC_MILISECOND_ADDR,&epocMillishRTC,sizeof(epocMillishRTC));
  } 
}

void epochMillisRTC()
{
  epocMillishRTC++;
}


void setup()
{
  RTC_Write_Memory(RTC_UTC_MILISECOND_ADDR,&epocMillishRTC,sizeof(epocMillishRTC));

  timer2.start();
  timer1.start();
 
}

void loop()
{
  timer1.update();
  timer2.update(); 
}
*/