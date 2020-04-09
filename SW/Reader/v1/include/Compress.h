#ifndef __COMPRESS_H__
#define __COMPRESS_H__

#include "types.h"

typedef enum : u8
{
    c_Original = 0,
    c_Compressed
} CompressType_t;

typedef struct
{
    CompressType_t type;
    u16 original_length;
    u16 compressed_length;
    u8 *data;
} CompressedData_t;

extern void CP_DestroyCompressedData(CompressedData_t *cd);
extern void CP_DestroyData(u8 *data);

//! Data Compression function which converts data-length into CompressedData_t
/*!
    \param data [input] : input buffer where the raw data come from
    \param length [input] : input buffer byte length
    \param out [output] : CompressedData_t which will contaion allocated and compressed or original data
    \return : true, if successfull
*/
extern bool CP_Compress(u8 *data, u16 length, CompressedData_t *out);

//! Data Decompression function which converts CompressedData_t into data-length
/*!
    \param in [input] : CompressedData_t
    \param data [output] : allocated and decompressed data buffer
    \param length [output] : length of data buffer which is equal to original_length
    \return : true, if successfull
*/
extern bool CP_Decompress(CompressedData_t *in, u8 **data, u16 *length);

#endif // __COMPRESS_H__