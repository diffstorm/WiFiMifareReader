#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "types.h"

//! The epoch function returns Unix timestamp for a date-time with year correction
/*!
  \param [in] dt : pointer to date-time struct
  \return timestamp in seconds
*/
time_t epoch(DateTime_t *dt);

u8 esp_rand();

u16 CRC16(u16 crc, unsigned char *i, unsigned int l);

#endif // __TOOLS_H__