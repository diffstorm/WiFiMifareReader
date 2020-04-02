#ifndef __CARD_H__
#define __CARD_H__

#include "CardConfig.h"

extern void Card_SetInfo(card_t *card, CardType_t type, DateTime_t record_date, UID_t uid);
extern void Card_SetPersonal(card_t *card, char *id, char *name, char *surname, char *mail, char *company, char *department);
extern void Card_SetNoPersonal(card_t *card);
//! \example : Card_SetRestrictions(&card, 8, 19, Saturday | Sunday);
extern void Card_SetRestrictions(card_t *card, u8 begin, u8 end, u8 dow);
extern void Card_SetNoRestrictions(card_t *card);
extern bool Card_isRestricted(card_t *card, u8 hour, Days_t today);

extern bool Card_UIDCompare(UID_t *uid, card_t *card);

extern void Card_cardRawDataDestroy(cardRaw_t *cardRaw);
extern card_t *Card_Create();
extern void Card_Destroy(card_t *card);

//! Convert a card object into cardRaw object
/*!
    \param card [input] : address of card object
    \param cardRaw [output] : address of cardRaw object with empty data
    \return : boolean, true if successful
*/
extern bool Card_Encapsulate(card_t *card, cardRaw_t *cardRaw);

//! Convert a cardRaw object into card object (free-s cardRaw data)
/*!
    \param cardRaw [input] : address of cardRaw object with non-empty data
    \param card [output] : address of card object
    \return : boolean, true if successful
*/
extern bool Card_Decapsulate(cardRaw_t *cardRaw, card_t *card);

//! Write cardRaw object into card sectors
/*!
    \param sector [input] : sector index
    \param cardRaw [input] : address of cardRaw object with non-empty data
    \param data [output] : data, ready to write into a card sector
    \return : boolean, true if successful
*/
extern bool Card_GetSector(u8 sector, cardRaw_t *cardRaw, u8 data[CARD_ROW_SIZE]);

//! Read card sectors into cardRaw object
/*!
    \param sector [input] : sector index
    \param data [input] : data, has been read from a card sector
    \param cardRaw [output] : address of cardRaw object with empty data
    \return : boolean, true if successful
*/
extern bool Card_SetSector(u8 sector, u8 data[CARD_ROW_SIZE], cardRaw_t *cardRaw);

#endif // __CARD_H__