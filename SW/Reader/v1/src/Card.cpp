#include "Card.h"
#include "tools.h"
//#include "crypto/crypto.h"

// TODO : card_t getters and setters
// TODO : add crypto

u16 Card_CalcPadding(u16 size, u16 mult)
{
    u16 padding = size % mult;
    if(padding > 0)
    {
        padding = mult - padding;
    }

    return padding;
}

bool Card_cardRawDataCreate(cardRaw_t *cardRaw)
{
    cardRaw->data = (u8 *)malloc(cardRaw->length);
    return (NULL != cardRaw->data);
}

void Card_cardRawDataDestroy(cardRaw_t *cardRaw)
{
    if(NULL != cardRaw->data)
    {
        free(cardRaw->data);
        cardRaw->data = NULL;
    }
}

bool Card_Validate(cardRaw_t *cardRaw)
{
    bool ret = false;
    u16 checksum_card = cardRaw->checksum;
    u16 checksum_calc;
    u16 bcc = cardRaw->checksum + cardRaw->length + cardRaw->random;

    if(cardRaw->bcc == bcc)
    {
        checksum_calc = CRC16(CARD_CHECKSUM_SEED, (u8 *)cardRaw->data, (unsigned int)cardRaw->length);
        if(checksum_calc == checksum_card)
        {
            ret = true;
        }
    }

    return ret;
}

card_t *Card_Create()
{
    card_t *card = (card_t *)malloc(sizeof(card_t));

    return card;
}

void Card_Destroy(card_t *card)
{
    if(NULL != card)
    {
        free(card);
    }
}

//! Convert a card object into cardRaw object
/*!
    \param card [input] : address of card object
    \param cardRaw [output] : address of cardRaw object with empty data
    \return : boolean, true if successful
*/
bool Card_Encapsulate(card_t *card, cardRaw_t *cardRaw)
{
    bool ret = false;
    u16 i;
    u16 size = sizeof(card_t);
    u16 padding = Card_CalcPadding(size, CARD_ROW_SIZE);
    size += padding;

    cardRaw->length = size;
    if(Card_cardRawDataCreate(cardRaw))
    {
        memcpy(cardRaw->data, card, sizeof(card_t));
        // TODO : encrypt(cardRaw->data, cardRaw->length, cardRaw->data)
        cardRaw->checksum = CRC16(CARD_CHECKSUM_SEED, (u8 *)cardRaw->data, (unsigned int)cardRaw->length);
        cardRaw->random = MAKE16(esp_rand(), esp_rand());
        cardRaw->bcc = cardRaw->checksum + cardRaw->length + cardRaw->random;
        ret = true;
    }

    return ret;
}

//! Convert a cardRaw object into card object (free-s cardRaw data)
/*!
    \param cardRaw [input] : address of cardRaw object with non-empty data
    \param card [output] : address of card object
    \return : boolean, true if successful
*/
bool Card_Decapsulate(cardRaw_t *cardRaw, card_t *card)
{
    bool ret = false;
    if(false != Card_Validate(cardRaw))
    {
        // TODO : decrypt(cardRaw->data, cardRaw->length, cardRaw->data)
        memcpy(card, cardRaw->data, sizeof(card_t));
        ret = true;
    }
    Card_cardRawDataDestroy(cardRaw);

    return ret;
}

//! Write cardRaw object into card sectors
/*!
    \param sector [input] : sector index
    \param cardRaw [input] : address of cardRaw object with non-empty data
    \param data [output] : data, ready to write into a card sector
    \return : boolean, true if successful
*/
bool Card_GetSector(u8 sector, cardRaw_t *cardRaw, u8 data[CARD_ROW_SIZE])
{
    bool ret = false;
    u8 *p = data;
    u16 index;

    if(0 == sector)
    {
        memcpy(p, (u8 *)&cardRaw->checksum, sizeof(cardRaw->checksum));
        p += sizeof(cardRaw->checksum);
        memcpy(p, (u8 *)&cardRaw->length, sizeof(cardRaw->length));
        p += sizeof(cardRaw->length);
        memcpy(p, (u8 *)&cardRaw->random, sizeof(cardRaw->random));
        p += sizeof(cardRaw->random);
        memcpy(p, (u8 *)&cardRaw->bcc, sizeof(cardRaw->bcc));
        p += sizeof(cardRaw->bcc);
        memset(p, 0, CARD_ROW_SIZE - (p - data));
        ret = true;
    }
    else
    {
        index = (sector - 1) * CARD_ROW_SIZE;
        if(cardRaw->length < index + CARD_ROW_SIZE)
        {
            memcpy(p, cardRaw->data + index, CARD_ROW_SIZE);
            ret = true;
        }
    }

    return ret;
}

//! Read card sectors into cardRaw object
/*!
    \param sector [input] : sector index
    \param data [input] : data, has been read from a card sector
    \param cardRaw [output] : address of cardRaw object with empty data
    \return : boolean, true if successful
*/
bool Card_SetSector(u8 sector, u8 data[CARD_ROW_SIZE], cardRaw_t *cardRaw)
{
    bool ret = false;
    u8 *p = data;
    u16 index;

    if(0 == sector)
    {
        memcpy((u8 *)&cardRaw->checksum, p, sizeof(cardRaw->checksum));
        p += sizeof(cardRaw->checksum);
        memcpy((u8 *)&cardRaw->length, p, sizeof(cardRaw->length));
        p += sizeof(cardRaw->length);
        memcpy((u8 *)&cardRaw->random, p, sizeof(cardRaw->random));
        p += sizeof(cardRaw->random);
        memcpy((u8 *)&cardRaw->bcc, p, sizeof(cardRaw->bcc));
        //p += sizeof(cardRaw->bcc);
        ret = (cardRaw->bcc == cardRaw->checksum + cardRaw->length + cardRaw->random);
        if(false != ret)
        {
            Card_cardRawDataDestroy(cardRaw);
            ret = Card_cardRawDataCreate(cardRaw);
        }
    }
    else
    {
        index = (sector - 1) * CARD_ROW_SIZE;
        if(cardRaw->length < index + CARD_ROW_SIZE)
        {
            memcpy(cardRaw->data + index, p, CARD_ROW_SIZE);
            ret = true;
        }
    }

    return ret;
}

void example()
{
    u8 sector;
    u8 data[CARD_ROW_SIZE];
    cardRaw_t cardRaw;
    card_t *card;

    //-------------------------------------------------------------

    // Create & Write a card object into card
    card = Card_Create();
    if(NULL != card)
    {
        // Fill the card object
        // e.g card->info.type = ct_USER;
        if(false != Card_Encapsulate(card, &cardRaw))
        {
            sector = 0;
            while(false != Card_GetSector(sector, &cardRaw, data))
            {
                // Write data to sector 0..N
                sector++;
            }
            Card_cardRawDataDestroy(&cardRaw);
        }
        Card_Destroy(card);
    }

    //-------------------------------------------------------------

    // Read a card into card object
    for(sector = 0; sector < CARD_SECTOR_SIZE; sector++)
    {
        // Read sector 0..N into data
        if(false == Card_SetSector(sector, data, &cardRaw))
        {
            break;
        }
    }
    card = Card_Create();
    if(NULL != card)
    {
        if(false != Card_Decapsulate(&cardRaw, card))
        {
            // Use the card object
            // e.g. SearchInWhiteList(card.info.uid.uid, card.info.uid.length)
        }
        Card_Destroy(card);
    }
}
