#include "Compress.h"
#include "tools.h"
#include "DebugLog.h"

#define COMPRESS_MAX_SIZE(s) (s + (s / 127) + 1)

//! RLE Compression Encoder function
/*!
    \param i [input] : input buffer where the raw data come from
    \param l [input] : input buffer byte length
    \param o [output] : output buffer which will contaion compressed data
    \return : byte length of output buffer o (compressed length)
*/
u16 RLE_encode(u8 *i, u16 l, u8 *o)
{
    u16 b = 0, c = 0, x, j;
    u8 d;

    while(c < l)
    {
        x = c;
        d = i[x++];
        while(x < l && x - c < 127 && i[x] == d)
        {
            x++;
        }
        if(x - c == 1)
        {
            while(x < l && x - c < 127
                    && (i[x] != i[x - 1]
                        || (x > 1 && i[x] != i[x - 2])))
            {
                x++;
            }
            while(x < l && i[x] == i[x - 1])
            {
                x--;
            }
            o[b++] = (u8)(c - x);
            for(j = c; j < x; j++)
            {
                o[b++] = i[j];
            }
        }
        else
        {
            o[b++] = (u8)(x - c);
            o[b++] = d;
        }
        c = x;
    }
    return (b);
}

//! RLE Compression Decoder function
/*!
    \param i [input] : input buffer contains previously compressed data
    \param l [input] : length of raw data used in encode function (not length of compressed input)
    \param o [output] : output buffer which will contain decompressed data
    \return : none
*/
void RLE_decode(u8 *i, u16 l, u8 *o)
{
    signed char c;

    while(l > 0)
    {
        c = (signed char) * i++;
        if(c > 0)
        {
            memset(o, *i++, c);
        }
        else if(c < 0)
        {
            c = (signed char) - c;
            memcpy(o, i, c);
            i += c;
        }
        o += c;
        l -= c;
    }
}

void CP_DestroyCompressedData(CompressedData_t *cd)
{
    if(NULL != cd->data)
    {
        free(cd->data);
    }
    memset(cd, 0, sizeof(CompressedData_t));
}

void CP_DestroyData(u8 *data)
{
    if(NULL != data)
    {
        free(data);
    }
}

//! Data Compression function which converts data-length into CompressedData_t
/*!
    \param data [input] : input buffer where the raw data come from
    \param length [input] : input buffer byte length
    \param out [output] : CompressedData_t which will contaion allocated and compressed or original data
    \return : true, if successfull
*/
bool CP_Compress(u8 *data, u16 length, CompressedData_t *out)
{
    bool ret = false;
    u8 *compressed_buffer;
    u16 compressed_length;
    u8 *out_buffer;
    u16 out_length;

    if(NULL != out->data)
    {
        free(out->data);
    }

    compressed_buffer = (u8 *)malloc(COMPRESS_MAX_SIZE(length));
    if(NULL != compressed_buffer)
    {
        compressed_length = RLE_encode(data, length, compressed_buffer);
        out->original_length = length;
        out->compressed_length = compressed_length;
        if(length > compressed_length + sizeof(CompressedData_t))
        {
            out->type = c_Compressed;
            out_length = compressed_length;
            out_buffer = compressed_buffer;
        }
        else
        {
            out->type = c_Original;
            out_length = length;
            out_buffer = data;
        }

        out->data = (u8 *)malloc(out_length);
        if(NULL != out->data)
        {
            memcpy(out->data, out_buffer, out_length);
            ret = true;
        }
        free(compressed_buffer);
    }

    return ret;
}

//! Data Decompression function which converts CompressedData_t into data-length
/*!
    \param in [input] : CompressedData_t
    \param data [output] : allocated and decompressed data buffer
    \param length [output] : length of data buffer which is equal to original_length
    \return : true, if successfull
*/
bool CP_Decompress(CompressedData_t *in, u8 **data, u16 *length)
{
    bool ret = false;

    if(NULL != *data)
    {
        free(*data);
    }
    *data = (u8 *)malloc(in->original_length);
    if(NULL != *data)
    {
        switch(in->type)
        {
            case c_Compressed:
                RLE_decode(in->data, in->original_length, *data);
                *length = in->original_length;
                ret = true;
                break;
            case c_Original:
            default:
                memcpy(*data, in->data, in->original_length);
                *length = in->original_length;
                ret = true;
                break;
        }
    }

    return ret;
}

void example()
{
    bool ret;
    u8 data[] = "Theeeeee quuuuiiiickkkk broooooowwwwwn fooooooxxxxxxx jjjjjjjjuuuuumpssssssss ooooverrrrrrrrrrrrr thhhhhhhhhhheeeee laaaaaaaaaazy dooooooooooog";
    u8 *data2;
    u16 length = sizeof(data);
    u16 length2;
    u16 outlength;
    CompressedData_t cd;

    ret = CP_Compress(data, length, &cd);
    if(false != ret)
    {
        LOG("[Compress] success");
        LOGd("[Compress] Original size : ", cd.original_length);
        LOGd("[Compress] Compressed size : ", cd.compressed_length);
        if(c_Compressed == cd.type)
        {
            outlength = cd.original_length - cd.compressed_length;
            LOGd("[Compress] size reduction : ", outlength);
        }
        else
        {
            LOG("[Compress] size reduction failed!");
        }
        LOGb("[Compress] Data : ", cd.data, cd.compressed_length);
    }
    else
    {
        LOG("[Compress] error!");
    }

    ret = CP_Decompress(&cd, &data2, &length2);
    if(false != ret)
    {
        LOGd("[Decompress] Original size : ", cd.original_length);
        LOGd("[Decompress] Compressed size : ", cd.compressed_length);
        LOGd("[Decompress] Decompressed size : ", length2);
        LOGb("[Decompress] Data : ", data2, length2);
        LOG(data2);
    }
    else
    {
        LOG("[Decompress] error!");
    }

    CP_DestroyCompressedData(&cd);

    if(length == length2 && 0 == memcmp(data, data2, length))
    {
        LOG("[Compare] Test success");
    }
    else
    {
        LOG("[Compare] Test failed!");
    }

    CP_DestroyData(data2);
}