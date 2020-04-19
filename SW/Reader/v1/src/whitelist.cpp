#include<whitelist.h>
#include<FileSystem.h>
#include <tools.h>

#define CRCUID 0xDEAD
#define MAX_UID_SIZE 500
#define MAX_NAMES_SIZE 2000
#define MAX_RECORD_NUMBER 50

char *crcUid = "/crcUid";
char *uidFILE1 = "/uid1";
char *names1 = "/names1";
char *uidFILE2 = "/uid2";
char *names2 = "/names2";
char *uidFILE3 = "/uid3";
char *names3 = "/names3";
char *uidFILE4 = "/uid4";
char *names4 = "/names4";
char *uidFILE5 = "/uid5";
char *names5 = "/names5";


//char *tempFILE2 = "/temp2";
/*const u16 crc16t[256] =
{
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

// CRC16 checksum function with precalculated table
// param i : input buffer
// param l : input buffer byte length
// return  : CRC16 checksum of input buffer with length l
u16 CRC16(u16 crc, unsigned char *i, unsigned int l)
{
    unsigned int x;

    for(x = 0; x < l; x++)
    {
        crc = (crc << 8) ^ crc16t[(crc >> 8) ^ i[x]];
    }

    return crc;
}
*/

u16 crcBuf[250];
u16 buf[1];
char* choosenUid;
char* choosenNames;
char* LastUid;
char* LastNames;

void WH_setFileName()
{

    if(FILE_check_size(uidFILE1)<MAX_UID_SIZE)
    {
        choosenUid = uidFILE1;
        choosenNames = names1;
    }
    else if(FILE_check_size(uidFILE2)<MAX_UID_SIZE)
    {
        choosenUid = uidFILE2;
        choosenNames = names2;
    }
    else if(FILE_check_size(uidFILE3)<MAX_UID_SIZE)
    {
        choosenUid = uidFILE3;
        choosenNames = names3;
    }
    else if(FILE_check_size(uidFILE4)<MAX_UID_SIZE)
    {
        choosenUid = uidFILE4;
        choosenNames = names4;
    }
    else
    {
        choosenUid = uidFILE5;
        choosenNames = names5;
    } 

}
void WH_getLastFileName()
{
    u8 i=0;
    u32 posEnd = FILE_check_size(crcUid) - sizeof(whitelist_UID_t) - 1;
    i = posEnd / MAX_RECORD_NUMBER;
    switch (i)
    {
    case 0:
        LastUid = uidFILE1;
        LastNames = names1;
        break;
    case 1:
        LastUid = uidFILE2;
        LastNames = names2;
        break;
    case 2:
        LastUid = uidFILE3;
        LastNames = names3;
        break;
    case 3:
        LastUid = uidFILE4;
        LastNames = names4;
        break;
    default:
        LastUid = uidFILE5;
        LastNames = names5;
        break;
    }
}

void WH_getFileName(u32 pos)
{
    
    u8 i=0; 
    i=pos/MAX_RECORD_NUMBER;
    switch (i)
    {
    case 0:
        choosenUid = uidFILE1;
        choosenNames = names1;
        break;
    case 1:
        choosenUid = uidFILE2;
        choosenNames = names2;
        break;
    case 2:
        choosenUid = uidFILE3;
        choosenNames = names3;
        break;
    case 3:
        choosenUid = uidFILE4;
        choosenNames = names4;
        break;
    default:
        choosenUid = uidFILE5;
        choosenNames = names5;
        break;
    }
}


bool WH_updateFile(char *name, char *name2, void *context, u32 length, u32 pos)  // nameden oku name2 ye yaz (name son dosyanın ismi olacak)
{
    bool ret = false;
    File f = SPIFFS.open(name, "r+");

    if(NULL != f)
    {

        if(true==f.seek((f.size() - length),SeekMode::SeekSet))
        {
            
            if(true==FILE_read_internal(&f, context, length))
            {
                f.close();
                File f1 = SPIFFS.open(name2, "r+");
                if(NULL != f1)
                {
                    if(true==f1.seek(pos*length, SeekMode::SeekSet))
                    {
                        if(true==FILE_write_internal(&f1, context,length))
                        {
                            f1.close();  
                            ret=true;
                        }
                    }
                }
            }
        }

    
    }

    return ret;
}

void WH_add(whitelist_t wl)
{
    WH_setFileName();
    u16 crc;
    FILE_Append(choosenUid, &wl, (u32)wl.uid.length);
    crc = CRC16(CRCUID, (u8 *)wl.uid.uid, (unsigned int)wl.uid.length);
    Serial.println("whadd crc: ");
    Serial.println(crc);
    FILE_Append(crcUid, &crc, sizeof(crc));
    FILE_Append(choosenNames, &wl.name, sizeof(wl.name));
    FILE_Append(choosenNames, &wl.surname, sizeof(wl.surname));
}

bool WH_searchUID(byte uid[], size_t len)
{
    bool ret = false;
    u16 crc1;
    u32 pos = 0;
    crc1 = CRC16(CRCUID, (u8 *)uid, (unsigned int)len);

    whitelist_t wl;

    FILE_Read(crcUid, &crcBuf, FILE_check_size(crcUid), 0); 


    for(size_t i = 0; i < FILE_check_size(crcUid) / sizeof(u16); i++)
    {

        if(crcBuf[i] == crc1)
        {
            pos=i;
            WH_getFileName(pos);
            pos = (i  % MAX_RECORD_NUMBER) * sizeof(wl.uid.uid);
            FILE_Read(choosenUid, &wl, wl.uid.length, pos);
            
            if(0 == memcmp(wl.uid.uid, uid, wl.uid.length))
            {
                ret = true;
                break;
            }
        }
    }
    Serial.printf("silinen kontrol : %d\n", ret);
    return ret;

}



bool WH_delete(byte uid[], size_t len)
{
    
    bool ret = false;
    u16 crc1;
    u32 pos = 0;
    
    whitelist_t wl;

    crc1 = CRC16(CRCUID, (u8 *)uid, (unsigned int)len);

    
    Serial.println(FILE_check_size(crcUid));
    FILE_Read(crcUid, &crcBuf, FILE_check_size(crcUid), 0);

    

    for(size_t i = 0; i < FILE_check_size(crcUid) / sizeof(u16); i++)
    {
        if(crcBuf[i] == crc1)
        {
            pos=i;
            WH_getFileName(pos);

            pos = (i  % MAX_RECORD_NUMBER) * sizeof(wl.uid.uid);
            
            FILE_Read(choosenUid, &wl, wl.uid.length, pos);

            if(0 == memcmp(wl.uid.uid, uid, wl.uid.length))
            {

                pos = i;
                FILE_update(crcUid, &buf, sizeof(buf), pos);
                FILE_Read(crcUid, &crcBuf, FILE_check_size(crcUid) - sizeof(u16), 0);
                FILE_Write(crcUid, &crcBuf, FILE_check_size(crcUid) - sizeof(u16));  
                FILE_Read(crcUid, &crcBuf, FILE_check_size(crcUid), 0);

                ///////////////////////////////////////
                
                WH_getFileName(pos);  
                WH_getLastFileName();
                pos = (i  % MAX_RECORD_NUMBER) * sizeof(wl.uid.uid);
                WH_updateFile(LastUid, choosenUid, &wl, wl.uid.length, pos); 

                u8 *ptr2;
                ptr2(u8 *) malloc(MAX_UID_SIZE);
                FILE_Read(LastUid,ptr2,FILE_check_size(choosenUid)-sizeof(wl.uid.uid),0);
                FILE_Write(LastUid,ptr2,FILE_check_size(choosenUid)-sizeof(wl.uid.uid));
                free(ptr2);
                ///////////////////////////////////////////////////
                
                pos = (i * (sizeof(wl.name) + sizeof(wl.surname))) % MAX_RECORD_NUMBER; 
                WH_updateFile(LastNames, choosenNames, &wl, (sizeof(wl.name) + sizeof(wl.surname)), pos);
               
                u8 *ptr3;
                ptr3 = (u8 *) malloc(MAX_NAMES_SIZE);
                FILE_Read(LastNames,ptr3,FILE_check_size(choosenNames)-(sizeof(wl.name) + sizeof(wl.surname),0);
                FILE_Write(LastNames,ptr3,FILE_check_size(choosenNames)-(sizeof(wl.name) + sizeof(wl.surname));
                free(ptr3);

                ret = true;
                break;
            }
        }

    }
    Serial.printf("silme ret: %d\n", ret);

    return ret;



}


