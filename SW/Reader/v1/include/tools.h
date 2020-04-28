#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "types.h"

u8 esp_rand();

u16 CRC16(u16 crc, unsigned char *i, unsigned int l);

//! The UTL_strcpy function copies s2 to s1 and returns last pointer of s1
/*!
  \param [in] s1       : Input string buffer (destination)
  \param [in] s2       : Input string buffer (source)
  \return last pointer of s1
*/
char *pstrcpy(char *s1, const char *s2);
#endif // __TOOLS_H__