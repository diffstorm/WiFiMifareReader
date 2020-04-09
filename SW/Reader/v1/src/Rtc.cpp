#include <Rtc.h>

extern "C"
{
#include "user_interface.h"
}

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

bool RTC_Write_Memory(RTCMemory_t* data,u16 len)
{
  bool ret = false;
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
      ret = true;
    }
  }
  return ret;
}

bool RTC_Read_Memory(RTCMemory_t* data,u16 len)
{
  bool ret = false;
  u16 padding = RTC_CalcPadding(len, RTC_MEMORY_BLOCK);
  len += padding;
  if (0 != system_rtc_mem_read(RTC_USER_DATA_ADDR, data, len))
  {
    yield();
    ret = true;
  }
  return ret;
}

bool RTC_Write_Time_Memory(RTC_time_t* time,u16 len)
{
  bool ret = false;
  if(512 < len)
  {
    if(0 !=system_rtc_mem_write(RTC_TIME_MEMORY,time,len))
    {
      ret = true;
    }
  }
  return ret;
}

bool RTC_Read_Time_Memory(RTC_time_t* time,u16 len)
{
  bool ret = false;
  if(512 < len)
  {
    if(0 !=system_rtc_mem_read(RTC_TIME_MEMORY,time,len))
    {
      ret = true;
    }
  }
  return ret;
}