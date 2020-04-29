#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "types.h"

//! The epoch function returns Unix timestamp for a date-time with year correction
/*!
  \param [in] dt : pointer to date-time struct
  \return timestamp in seconds
*/
extern time_t epoch(DateTime_t *dt);

//! HW True Random Number Generator of ESP8266
/*!
    \return : 8 bit random generated value
*/
extern u8 esp_rand();

//! CRC16 checksum function with precalculated table
/*!
    \param i : input buffer
    \param l : input buffer byte length
    \return  : CRC16 checksum of input buffer with length l
*/
extern u16 CRC16(u16 crc, unsigned char *i, unsigned int l);

//! The pstrcpy function copies s2 to s1 and returns last pointer of s1
/*!
  \param [in] s1       : Input string buffer (destination)
  \param [in] s2       : Input string buffer (source)
  \return last pointer of s1
*/
extern char *pstrcpy(char *s1, const char *s2);

#endif // __TOOLS_H__