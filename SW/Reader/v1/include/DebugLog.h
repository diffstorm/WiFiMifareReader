#ifndef __DEBUGLOG_H__
#define __DEBUGLOG_H__

#define DEBUG_LOG   1 // 1 : enable | 0 : disable

#if DEBUG_LOG
// Printout: message [int, float, double, hex] | <function_name> @ <file_name> : <line>
#ifndef __func__
#define __func__ __FUNCTION__
#endif

#define __S1(x) #x
#define __S2(x) __S1(x)
#define __LOCATION " @ " __FILE__ " : " __S2(__LINE__)

void DBG_LOG_Init(unsigned long baudrate);
void DBG_LOG_tail(const char *func, const char *loc);

#if 0
void DBG_LOG(const char *message, const char *func, const char *loc, int *i, float *f, double *d, char *hex, int hex_size);

#define LOG_Init(x) DBG_LOG_Init(x)
#define LOG(z)      DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, NULL, NULL, NULL, NULL, (int)0)
#define LOGi(z, i)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, (int *)&(i), NULL, NULL, NULL, (int)0)
#define LOGf(z, f)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, NULL, (float *)&(f), NULL, NULL, (int)0)
#define LOGd(z, d)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, NULL, NULL, (double *)&(d), NULL, (int)0)
#define LOGh(z, h)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, NULL, NULL, NULL, (char *)h, (int)sizeof(h))
#define LOGb(z, h, s)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, NULL, NULL, NULL, (char *)h, (int)s)
#else
typedef enum 
{
    dl_none,
    dl_int,
    dl_float,
    dl_double,
    dl_hex
} dl_type_t;
void DBG_LOG(const char *message, const char *func, const char *loc, dl_type_t type, void *in, int size);

#define LOG_Init(x) DBG_LOG_Init(x)
#define LOGp(fmt, ...)    Serial.printf(fmt, __VA_ARGS__); DBG_LOG_tail((const char *)__func__, (const char *)__LOCATION)
#define LOG(z)      DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, dl_none, (void *)NULL, (int)0)
#define LOGi(z, i)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, dl_int, (void *)&(i), (int)0)
#define LOGf(z, f)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, dl_float, (void *)&(f), (int)0)
#define LOGd(z, d)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, dl_double, (void *)&(d), (int)0)
#define LOGh(z, h)  DBG_LOG((const char *)z, (const char *)__func__,(const char *)__LOCATION,  dl_hex, (void *)h, (int)sizeof(h))
#define LOGb(z, h, s)  DBG_LOG((const char *)z, (const char *)__func__, (const char *)__LOCATION, dl_hex, (void *)h, (int)s)
#endif
#else
#define LOG_Init(x) ((void)0)
#define LOG(z)     ((void)0)
#define LOGi(z,i)  ((void)0)
#define LOGf(z,f)  ((void)0)
#define LOGd(z,d)  ((void)0)
#define LOGh(z,h)  ((void)0)
#define LOGb(z,h,s)  ((void)0)
#endif

#endif // __DEBUGLOG_H__
