#include "CardConfig.h"
#include "tools.h"

#define CARD_CHECKSUM_SEED   0xDEAD

bool Card_Validate(cardRaw_t *cardRaw)
{
    bool ret = false;
    u16 checksum_card = cardRaw->checksum;
    u16 checksum_calc;
    
    checksum_calc = CRC16(CARD_CHECKSUM_SEED, (u8 *)cardRaw->data, (unsigned int)cardRaw->length);
    
    if(checksum_calc == checksum_card)
    {
        ret = true;
    }
    
    return ret;
}

bool Card_Encapsulate(card_t *card, cardRaw_t *cardRaw)
{
    // TODO : decrypt(card, sizeof(card_t)), set cardRaw->data, cardRaw->length
    
    cardRaw->checksum = CRC16(CARD_CHECKSUM_SEED, (u8 *)card, (unsigned int)cardRaw->length);   
}

bool Card_Decapsulate(cardRaw_t *cardRaw, card_t *card)
{
    bool ret = false;
    if(false != Card_Validate(cardRaw)
    {
        // TODO : decrypt, set card_t
        
        ret = true;
    }
    
    return ret;
}

/*
void kart_yaz(card_t *card)
{
    cardRaw_t ec2;
    cardRaw_t ec = þifrele(card);
    yaz(ec);
    oku(&ec2);
    if(0 == memcmp(ec2, ec, sizeof(cardRaw_t))
    {
        return true;
    }
    return false;
}

void kart_oku(card_t *card)
{
    oku(card);
    þifreçöz(card);
    return hash_kontrol(card);
}
*/