#include <Rtc.h>
#include <SysTick.h>
#include "DebugLog.h"
#include "tools.h"

extern "C"
{
#include "user_interface.h"
}

u32 rtc_ms;
u32 rtc_elapsed;
u64 rtc_time;

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
    LOG("%s:\n", desc);

  if (len == 0)
  {
    LOG("  ZERO LENGTH\n");
    return;
  }
  if (len < 0)
  {
    LOG("  NEGATIVE LENGTH: %i\n", len);
    return;
  }

  for (i = 0; i < len; i++)
  {

    if ((i % 16) == 0)
    {

      if (i != 0)
        LOG("  %s\n", buff);

      LOG("  %04x ", i);
    }

    LOG(" %02x", pc[i]);

    if ((pc[i] < 0x20) || (pc[i] > 0x7e))
      buff[i % 16] = '.';
    else
      buff[i % 16] = pc[i];
    buff[(i % 16) + 1] = '\0';
  }

  while ((i % 16) != 0)
  {
    LOG("   ");
    i++;
  }

  LOG("  %s\n", buff);
}

bool RTC_Write_Memory(RTC_Memory_t *data)
{
  return system_rtc_mem_write(RTC_USER_ADDR, data, sizeof(RTC_Memory_t));
}

bool RTC_Read_Memory(RTC_Memory_t *data)
{
  return system_rtc_mem_read(RTC_USER_ADDR, data, sizeof(RTC_Memory_t));
}

u64 RTC_GetTime()
{
  return rtc_time;
}

u32 RTC_GetEpoch()
{
  return rtc_time / 1000;
}

void RTC_SetEpoch(u32 epoch)
{
  u64 t = epoch;
  rtc_time = t * 1000;
}

bool RTC_StoreTime(UTC_t utc)
{
  bool ret = false;
  RTC_Memory_t data;
  u16 crc;

  if (false != RTC_Read_Memory(&data))
  {
    crc = CRC16(0xDEAD, (u8 *)&utc, sizeof(UTC_t));
    data.time = utc;
    data.checksum = crc;
    if (false != RTC_Write_Memory(&data))
    {
      ret = true;
    }
  }

  return ret;
}

UTC_t RTC_RestoreTime()
{
  UTC_t ret = {0};
  RTC_Memory_t data;
  u16 crc;

  if (false != RTC_Read_Memory(&data))
  {
    crc = CRC16(0xDEAD, (u8 *)&data.time, sizeof(UTC_t));
    if (crc == data.checksum)
    {
      ret = data.time;
    }
  }
  else
  {
    LOG("RTC den saat bilgisi okunamadi");
  }

  return ret;
}

void RTC_Init()
{
  UTC_t time;
  rtc_ms = SysTick_get();
  time = RTC_RestoreTime();
  time.utc += time.startvalue;
  rtc_time = time.utc;
}

void RTC_Handler()
{
  rtc_elapsed = SysTick_elapsed(rtc_ms);
  rtc_ms += rtc_elapsed;
  rtc_time += rtc_elapsed;
}
