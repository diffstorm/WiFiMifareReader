#ifndef __WHITELIST_H__
#define __WHITELIST_H__

#include <stdint.h>
#include "CardConfig.h"

typedef struct __attribute__((packed))
{
    char name[CARD_CFG_NAME_LENGTH];
    char surname[CARD_CFG_NAME_LENGTH];
}
WL_detail_t;

typedef struct __attribute__((packed))
{
    UID_t uid;
    WL_detail_t detail;
}
WL_item_t;

void example_whitelist();

//! Adds given uid to whitelist
/*!
    \param item [input] : the struct which will be added to whitelist
    \return : boolean, true if successsful
*/
bool WL_add(WL_item_t item);

//! Deletes given uid from whitelist (not only uid, includes name surname and crc)
/*!
    \param uid [input] : the uid which will be deleted
    \return : boolean, true if successful
*/
bool WL_delete(UID_t uid);

//! Search given uid in whitelist
/*!
    \param uid [input] : the uid which will be searched
    \return : long, -1 if does not found, position if founds
*/
long WL_search(UID_t uid);

//! Reads data (at given index) inside to item
/*!
    \param index [input] : the index which will be read
    \param item [output] : the data will be read in to
    \return : boolean, true if successful
*/
bool WL_read(u16 index, WL_item_t *item);

#endif