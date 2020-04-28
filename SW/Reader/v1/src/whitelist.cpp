#include<whitelist.h>
#include<FileSystem.h>
#include <tools.h>
<<<<<<< Updated upstream

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


/*
const u16 crc16t[256] =
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

void WL_setFileName(char* filename, char* filename2)
{

    if(FILE_get_size(uidFILE1) < MAX_UID_SIZE)
    {
        strcpy(filename,uidFILE1);
        strcpy(filename2,names1);
    }
    else if(FILE_get_size(uidFILE2) < MAX_UID_SIZE)
    {
        strcpy(filename,uidFILE2);
        strcpy(filename2,names2);
    }
    else if(FILE_get_size(uidFILE3) < MAX_UID_SIZE)
    {
        strcpy(filename,uidFILE3);
        strcpy(filename2,names3);
    }
    else if(FILE_get_size(uidFILE4) < MAX_UID_SIZE)
    {
        strcpy(filename,uidFILE4);
        strcpy(filename2,names4);
    }
    else if(FILE_get_size(uidFILE5) < MAX_UID_SIZE)
    {
        strcpy(filename,uidFILE5);
        strcpy(filename2,names5);
    }
    else
    {
        Serial.println("Error, system is full");  
    }
    

}

void WL_getLastFileName(char* filename, char* filename2)
{
    u8 i = 0;
    u32 posEnd = FILE_get_size(crcUid) / 2 ;
    i = posEnd / MAX_RECORD_NUMBER;
    switch(i)
    {
        case 0:
            strcpy(filename,uidFILE1);
            strcpy(filename2,names1);
            break;
        case 1:
            strcpy(filename,uidFILE2);
            strcpy(filename2,names2);
            break;
        case 2:
            strcpy(filename,uidFILE3);
            strcpy(filename2,names3);
            break;
        case 3:
            strcpy(filename,uidFILE4);
            strcpy(filename2,names4);
            break;
        case 4:
            strcpy(filename,uidFILE5);
            strcpy(filename2,names5);
            break;
        default:
            Serial.println("Error, position is wrong");
    }
}

void WL_getFileName(u32 pos,char* filename, char* filename2)
{

    u8 i = 0;
    i = (pos) / MAX_RECORD_NUMBER; 
    
    switch(i)
    {
        case 0:
            strcpy(filename,uidFILE1);
            strcpy(filename2,names1);
            break;
        case 1:
            strcpy(filename,uidFILE2);
            strcpy(filename2,names2);
            break;
        case 2:
            strcpy(filename,uidFILE3);
            strcpy(filename2,names3);
            break;
        case 3:
            strcpy(filename,uidFILE4);
            strcpy(filename2,names4);
            break;
        case 4:
            strcpy(filename,uidFILE5);
            strcpy(filename2,names5);
            break;
        default:
            Serial.println("error, position is wrong");
    }
}


bool WL_updateFile(char *name, char *name2, void *context, u32 length, u32 pos)  
{
    bool ret = false;
    File f = SPIFFS.open(name, "r+");

    if(NULL != f)
    {
        if(false != f.seek((f.size() - length), SeekMode::SeekSet))
        {
            if(false != FILE_read_internal(&f, context, length))
            {
                f.close();
                File f1 = SPIFFS.open(name2, "r+");
                if(NULL != f1)
                {
                    if(false != f1.seek(pos, SeekMode::SeekSet))
                    {
                        if(false != FILE_write_internal(&f1, context, length))
                        {
                            f1.close();
                            ret = true;
                        }
                    }
                }
            }
        }
=======
#include"DebugLog.h"


// TODO : debuglog implementasyonu
#define CRCUID              0xDEAD
#define MAX_ITEM_SIZE       250
#define MAX_ITEMS_IN_FILE   50
#define MAX_FILENAME_LENGTH 15

#define MAX_UID_SIZE        (MAX_ITEMS_IN_FILE * sizeof(UID_t))
#define MAX_DETAILS_SIZE    (MAX_ITEMS_IN_FILE * sizeof(WL_Detail_t))
#define MAX_FILE_NUMBER     (MAX_ITEM_SIZE / MAX_ITEMS_IN_FILE)

#define ERR_NO_SPACE        0xFF
#define WL_FileExtension    ".wl"
#define Filename_crcuid     "crcuid"
#define Filename_uid        "uid"
#define Filename_detail     "detail"


typedef enum {
    fn_CRCUID_List = 0,
    fn_UID_List,
    fn_Detail_List,
} WL_Filenames_t;

//! Gets file name
/*!
    \param fn [input] : file type
    \param index [input] : index for deciding filename
    \param filename [output] : got filename
*/
void WL_GetFileName(WL_Filenames_t fn, u8 index, char filename[MAX_FILENAME_LENGTH])
{
    char *p = filename;
    p = pstrcpy(p, FS_ROOTDIR);
    switch(fn) 
    {
        case fn_CRCUID_List:
        p = pstrcpy(p, Filename_crcuid);
        break;
        case fn_UID_List:
        p = pstrcpy(p, Filename_uid);
        *p++ = '0' + index;
        *p++ = NULL;
        break;
        case fn_Detail_List:
        p = pstrcpy(p,Filename_detail);
        *p++ = '0' + index;
        *p++ = NULL;
        break;
    }
    p = pstrcpy(p,WL_FileExtension);
    //LOG("[WL] getfilename: ");
    LOG(filename);
}

//! Gets last file index
/*!
    \return : u8, index
*/
u8 WL_getLastFileIndex()
{
    u8 index;
    char fn[MAX_FILENAME_LENGTH];

    WL_GetFileName(fn_CRCUID_List, 0, fn);
    u32 posEnd = FILE_get_size(fn) / sizeof(u16);
    index = posEnd / MAX_ITEMS_IN_FILE;

    if(MAX_FILE_NUMBER <= index)
    {
        LOG("Error, position is wrong");
        index = ERR_NO_SPACE;
    }

    return index;
}
//! Gets current file index
/*!
    \param pos [input] : position for deciding file index
    \return : u8, index
*/
u8 WL_getFileIndex(u32 pos)
{
    u8 index;

    index = (pos) / MAX_ITEMS_IN_FILE;   

    if(MAX_FILE_NUMBER <= index)
    {
        LOG("Error, position is wrong");
        index = ERR_NO_SPACE;     
    }

    return index;
}

// src indexdekini dst indexe kopyalar
//! Finds the src and dst files and reads from src, writes in to dst
/*!
    \param type [input] : file type
    \param src_index [input] : source index
    \param dst_index [input] : destination index
    \param context [input] : buffer data in to
    \param length [input] : how many data will be read
    \param pos [input] : write process nbeginning position
    \return : boolean, true if successful
*/
bool WL_copyItem(WL_Filenames_t type, u8 src_index, u8 dst_index, void *context, u32 length, u32 pos)  
{
    bool ret = false;
    char fn[MAX_FILENAME_LENGTH];

    WL_GetFileName(type, src_index, fn);
    size_t size = FILE_get_size(fn);
    if(false != FILE_Read(fn, context, length, size - length))
    {
        WL_GetFileName(type, dst_index, fn);
        if(false != FILE_update(fn, context, length, pos))
        {
            ret = true;
        }
    }

    return ret;
}


//! Cuts the last item in file
/*!
    \param type [input] : file type
    \param index [input] : index for decide file
    \param length [input] : decides new file size 
    \return : boolean, true if successful
*/
bool WL_cutLastItem(WL_Filenames_t type, u8 index, u32 length)  
{
    bool ret = false;
    char fn[MAX_FILENAME_LENGTH];
    u8 *p;
    u32 size;

    WL_GetFileName(type, index, fn);
    size = FILE_get_size(fn);
    if(size >= length)
    {
        size -= length;
    }

    if(0 < size)
    {
        p = (u8 *) malloc(size);
        if(NULL != p)
        {
            if(false != FILE_Read(fn, p, size, 0))
            {
                if(false != FILE_Write(fn, p, size))
                {
                    ret = true;
                    //Serial.println("file updated");
                    LOGd("[WL] cut item- size of updated crc file: ", size);
                }
            }
            free(p);
        }
        else
        {
            LOG("Memory allocation error");
        }
    }
    else
    {
        if(false != FILE_delete(fn))
        {
            LOG("File removed");
        }
    }
    
    return ret;
}

u32 WL_GetSafeSize(char *filename, u32 buffersize, u32 *filesize) // Okunacak verinin buffer boyutunu asmasini engeller
{
    u32 ret;

    ret = FILE_get_size(filename);
    *filesize = ret;
    if(buffersize < ret)
    {
        ret = buffersize;
>>>>>>> Stashed changes
    }

    return ret;
}

<<<<<<< Updated upstream
long WL_searchUID(byte uid[], size_t len)
{
    long ret = -1;
    u16 crc1;
    u32 pos = 0;
    whitelist_t wl;
    char currentUidFile[10];
    char currentNameFile[10];

    crc1 = CRC16(CRCUID, (u8 *)uid, (unsigned int)len);

    if(false != FILE_Read(crcUid, &crcBuf, FILE_get_size(crcUid), 0))
    {
        for(size_t i = 0; i < FILE_get_size(crcUid) / sizeof(u16); i++)
        {

            if(crcBuf[i] == crc1)
            {

                pos = i;
                WL_getFileName(pos,currentUidFile,currentNameFile);
                pos = (i % MAX_RECORD_NUMBER) * sizeof(wl.uid.uid);
                if(false != FILE_Read(currentUidFile, &wl, len, pos))
                {
                    if(0 == memcmp(wl.uid.uid, uid, len))
                    {
                        ret = i;
                        Serial.printf("[WL]-> search-> find in: %s\n",currentUidFile);
                        Serial.printf("[WL]-> search-> position: %d\n", pos);
=======
//! Search given uid in whitelist
/*!
    \param uid [input] : the uid which will be searched
    \return : long, -1 if does not found, position if founds
*/
long WL_search(UID_t uid)
{
    long ret = -1;
    u16 crc;
    u32 size, readsize;
    u32 pos = 0;
    UID_t ruid;
    char fn[MAX_FILENAME_LENGTH];
    u16 crcuid_list[MAX_ITEM_SIZE];

    crc = CRC16(CRCUID, (u8 *)&uid, (unsigned int)sizeof(UID_t));

    WL_GetFileName(fn_CRCUID_List, 0, fn);
    memset((u8*)&crcuid_list, 0, sizeof(crcuid_list));
    readsize = WL_GetSafeSize(fn, sizeof(crcuid_list), &size);
    if(false != FILE_Read(fn, &crcuid_list[0], readsize, 0))
    {
        for(size_t i = 0; i < size / sizeof(u16); i++)
        {
            if(crcuid_list[i] == crc)
            {
                WL_GetFileName(fn_UID_List, WL_getFileIndex(i), fn);
                pos = (i % MAX_ITEMS_IN_FILE) * sizeof(UID_t);
                if(false != FILE_Read(fn, &ruid, sizeof(UID_t), pos))
                {
                    if(0 == memcmp(&uid, &ruid,  sizeof(UID_t)))
                    {
                        ret = i;
                        //LOG("[WL] add - find in: ");
                        //LOG(fn);
                        LOGd("[WL] add - position: ",pos);
                        //Serial.printf("[WL]-> search-> find in: %s\n", fn);
                        //Serial.printf("[WL]-> search-> position: %d\n", pos);
>>>>>>> Stashed changes
                        break;
                    }
                }
            }
        }
        
    }
<<<<<<< Updated upstream
    return ret;

}


bool WL_delete(byte uid[], size_t len)
=======

    return ret;
}

//! Deletes given uid from whitelist (not only uid includes name surname and crc)
/*!
    \param uid [input] : the uid which will be deleted
    \return : boolean, true if successful
*/
bool WL_delete(UID_t uid)
>>>>>>> Stashed changes
{

    bool ret = false;
    u8 control=0;
<<<<<<< Updated upstream
    u16 buf[1];
    whitelist_t wl;
    char currentUidFile[10];
    char currentNameFile[10];
    char LastUidFile[10];
    char LastNameFile[10];

    long pos = WL_searchUID(uid,len); 

    if(0<=pos)
    {

        if(false != WL_updateFile(crcUid, crcUid, &buf, sizeof(buf), pos))
        {
            if(false != FILE_Read(crcUid, &crcBuf, FILE_get_size(crcUid) - sizeof(u16), 0))
            {
                if(false != FILE_Write(crcUid, &crcBuf, FILE_get_size(crcUid) - sizeof(u16)))
                {
                    if(false != FILE_Read(crcUid, &crcBuf, FILE_get_size(crcUid), 0))
                    {
                        control++;
                        Serial.println("crc file updated");
                    }
                }
            }
        }
        ///////////////////////////////////////

        WL_getFileName(pos,currentUidFile,currentNameFile);
        WL_getLastFileName(LastUidFile,LastNameFile);
        //////////////////////////////////////////////////////
        pos = (pos  % MAX_RECORD_NUMBER) * sizeof(wl.uid.uid);

        if(false != WL_updateFile(LastUidFile, currentUidFile, &wl, sizeof(wl.uid.uid), pos))
        {
            u8 *ptr2;
            ptr2 = (u8 *) malloc(MAX_UID_SIZE);
            if(ptr2 == NULL)
            {
                Serial.println("Memory allocation error");
            }
            else
            { 
                if(false != FILE_Read(LastUidFile, ptr2, FILE_get_size(LastUidFile) - sizeof(wl.uid.uid), 0))
                {
                    if(false != FILE_Write(LastUidFile, ptr2, FILE_get_size(LastUidFile) - sizeof(wl.uid.uid)))
                    {
                        free(ptr2);
                        control++;
                        Serial.println("uid file updated");
                    }
                }
=======
    u16 crc;
    UID_t ruid;
    WL_detail_t rdetail;
    u8 fileindex;          // 0 ile 5 arasında değer döner
    long itempos;            //dosyanın başından itibaren byte bazında pozisyon döner
    u8 lastfileindex;

    long pos = WL_search(uid); // 0 ile 250 arasında değer döner

    if(0 <= pos)
    {
        lastfileindex = WL_getLastFileIndex();
        fileindex = WL_getFileIndex(pos);
               
        if(false != WL_copyItem(fn_CRCUID_List, lastfileindex, fileindex, &crc, sizeof(u16), pos))
        {
            if(false != WL_cutLastItem(fn_CRCUID_List, 0, sizeof(u16)))
            {
                control++;
                LOG("crc file updated");
                
                //Serial.println("crc file updated");      
            }
        }
        ///////////////////////////////////////
        
        itempos = (pos % MAX_ITEMS_IN_FILE) * sizeof(UID_t);
        if(false != WL_copyItem(fn_UID_List, lastfileindex, fileindex, &ruid, sizeof(UID_t), itempos))
        {
            if(false != WL_cutLastItem(fn_UID_List, lastfileindex, sizeof(UID_t)))
            {
                control++;
                LOG("uid file updated");
                //Serial.println("uid file updated");      
>>>>>>> Stashed changes
            }
        }
        ///////////////////////////////////////////////////
                    
<<<<<<< Updated upstream
        pos = (pos  % MAX_RECORD_NUMBER)* (sizeof(wl.name) + sizeof(wl.surname));

        if(false != WL_updateFile(LastNameFile, currentNameFile, &wl, (sizeof(wl.name) + sizeof(wl.surname)), pos))   //kontrol edilecek
        { 

            u8 *ptr3;
            ptr3 = (u8 *) malloc(MAX_NAMES_SIZE);
            if(ptr3 == NULL)
            {
                Serial.println("Memory allocation error");
            }
            else
            { 
                if(false != FILE_Read(LastNameFile,ptr3,FILE_get_size(LastNameFile)-(sizeof(wl.name) + sizeof(wl.surname)),0))
                {
                    if(false != FILE_Write(LastNameFile, ptr3,FILE_get_size(LastNameFile)-(sizeof(wl.name) + sizeof(wl.surname))))
                    {
                        free(ptr3);
                        control++;
                        Serial.println("names file updated");
                    }
                }
            }
        }
=======
        itempos = (pos  % MAX_ITEMS_IN_FILE)* sizeof(WL_detail_t);
        if(false != WL_copyItem(fn_Detail_List, lastfileindex, fileindex, &rdetail, sizeof(WL_detail_t), itempos))
        {
            if(false != WL_cutLastItem(fn_Detail_List, lastfileindex, sizeof(WL_detail_t)))
            {
                control++;
                LOG("detail file updated");
                //Serial.println("detail file updated");      
            }
        }
        
    }
>>>>>>> Stashed changes

        if(3 == control)
        {
            ret = true;
        }
<<<<<<< Updated upstream

        Serial.printf("[WL]-> delete-> status: %d\n",ret);
        Serial.printf("[WL]-> delete-> uid file: %s\n",currentUidFile);
        Serial.printf("[WL]-> delete-> sizeof uid file: %d\n",FILE_get_size(currentUidFile));
        Serial.printf("[WL]-> delete-> name file: %s\n",currentNameFile);
        Serial.printf("[WL]-> delete-> sizeof name file: %d\n",FILE_get_size(currentNameFile));
        Serial.printf("[WL]-> delete-> crc file: %s\n",crcUid);
        Serial.printf("[WL]-> delete-> sizeof crc file: %d\n",FILE_get_size(crcUid));

        }


        return ret;



}


void WL_add(whitelist_t wl)
{

    char currentUidFile[10];
    char currentNameFile[10];
    u16 crc;

    WL_delete(wl.uid.uid, sizeof(wl.uid.uid));
    WL_setFileName(currentUidFile, currentNameFile); 
    crc = CRC16(CRCUID, (u8 *)wl.uid.uid, (unsigned int)wl.uid.length);
    Serial.print("[WL]-> add-> added crc: ");
    Serial.println(crc);
     
    if(false != FILE_Append(currentUidFile, &wl, sizeof(wl.uid.uid)))
    {
        if(false != FILE_Append(crcUid, &crc, sizeof(crc)))
        {
            if(false != FILE_Append(currentNameFile, &wl.name, sizeof(wl.name)))
            {
                if(false != FILE_Append(currentNameFile, &wl.surname, sizeof(wl.surname)))
                {
                    Serial.println("Add successful");
                }
            }
        }
    }

    Serial.printf("[WL]-> add-> uid file: %s\n",currentUidFile);
    Serial.printf("[WL]-> add-> sizeof uid file: %d\n",FILE_get_size(currentUidFile));
    Serial.printf("[WL]-> add-> name file: %s\n",currentNameFile);
    Serial.printf("[WL]-> add-> sizeof name file: %d\n",FILE_get_size(currentNameFile));
    Serial.printf("[WL]-> add-> crc file: %s\n",crcUid);
    Serial.printf("[WL]-> add-> sizeof crc file: %d\n",FILE_get_size(crcUid));
}



=======
        LOGi("[WL]-> delete-> status: ",ret);
        
        //Serial.printf("[WL]-> delete-> status: %d\n",ret);

        return ret;



}

//! Adds given uid to whitelist
/*!
    \param item [input] : the struct which will be added to whitelist
    \return : boolean, true if successsful
*/
bool WL_add(WL_item_t item)
{

    bool ret = false;
    char fn[MAX_FILENAME_LENGTH];
    u16 crc;
    u8 lastfileindex;

    WL_delete(item.uid);  //

    lastfileindex = WL_getLastFileIndex();
    if(MAX_FILE_NUMBER > lastfileindex)
    {
        crc = CRC16(CRCUID, (u8 *)&item.uid, sizeof(UID_t));
        LOGi("[WL]-> add-> added crc: ",crc);  // TODO pos ve crc değerleri çok büyük oldugu için u32 bastırabilecek bir debug log fonksiyonu
        //Serial.println(crc);

        WL_GetFileName(fn_CRCUID_List,0,fn);
        if(false != FILE_Append(fn, &crc, sizeof(u16)))
        {  
            Serial.printf("sizeof crc file: %d\n",FILE_get_size(fn));
            WL_GetFileName(fn_UID_List, lastfileindex,fn);
            if(false != FILE_Append(fn, &item.uid, sizeof(UID_t)))
            {   
                Serial.printf("sizeof uid file: %d\n",FILE_get_size(fn));
                WL_GetFileName(fn_Detail_List, lastfileindex,fn);
                if(false != FILE_Append(fn,&item.detail , sizeof(WL_detail_t)))    
                { 
                    Serial.printf("sizeof detail file: %d\n",FILE_get_size(fn));
                    ret= true;
                    LOG("add successful");
                    
                    //Serial.println("Add successful");
                    //Serial.println("Add successful");
                }
            }
        }
    }

    return ret;
}

//! Reads data (at given index) inside to item 
/*!
    \param index [input] : the index which will be read
    \param item [output] : the data will be read in to
    \return : boolean, true if successful
*/
bool WL_read(u16 index, WL_item_t *item)
{
   bool ret= false;
   UID_t ruid;
   WL_detail_t rdetail;
   u32 itempos;
   u8 fileindex = WL_getFileIndex(index);
   char fn[MAX_FILENAME_LENGTH];

   itempos = (index % MAX_ITEMS_IN_FILE) * sizeof(UID_t);
   WL_GetFileName(fn_UID_List,fileindex,fn);

   if(false != FILE_Read(fn,&ruid,sizeof(UID_t),itempos))
   {
        memcpy(&item->uid, &ruid, sizeof(UID_t));
        
        itempos = (index  % MAX_ITEMS_IN_FILE)* sizeof(WL_detail_t);

        WL_GetFileName(fn_Detail_List, fileindex, fn);

        if(false != FILE_Read(fn, &rdetail,sizeof(WL_detail_t),itempos))
        {
            memcpy(&item->detail, &rdetail, sizeof(WL_detail_t));     
            ret = true;        
        }  
        
   }
   
   return ret;  
}


////////////////////////////////////////////////////////////////////////////////////




u8 WL_GetAvailableFileIndex()
{
    u8 index;
    char fn[MAX_FILENAME_LENGTH];

    for(index=0; index < MAX_FILE_NUMBER; index++)
    {
        WL_GetFileName(fn_UID_List, index, fn);
        if(FILE_get_size(fn) < MAX_UID_SIZE)
        {
            break;
        }
    }
    
    if(MAX_FILE_NUMBER == index)
    {
        Serial.println("Error, system is full");
        index = ERR_NO_SPACE; 
    }
    
    return index;
}




void example_whitelist()
{
    u8 i;

    typedef struct 
    {
        WL_item_t white[36];
        WL_item_t black;
        WL_item_t white1;
        WL_item_t white2;
        WL_item_t white3;
        WL_item_t white4;
        WL_item_t white5;
        WL_item_t white6;
        WL_item_t white7;
        WL_item_t white8;
        WL_item_t white9;
        WL_item_t white55;
        WL_item_t item;
    }t_t;

    t_t *t = (t_t *) malloc(sizeof(t_t));

    t->black.uid.length = 10;
    t->white1.uid.length = 10;
    t->white2.uid.length = 10;
    t->white3.uid.length = 10;
    t->white4.uid.length = 10;
    t->white5.uid.length = 10;
    t->white6.uid.length = 10;
    t->white7.uid.length = 10;
    t->white8.uid.length = 10;
    t->white9.uid.length = 10;
    t->white55.uid.length = 10;

    strcpy(t->white1.detail.name, "oguzhan");
    strcpy(t->white1.detail.surname, "alkis");

    for(i = 0; i < 10; i++)
    {
        t->white1.uid.uid[i] = 1;
    }
    for(i = 0; i < 10; i++)
    {
        t->white2.uid.uid[i] = 2;
    }
    for(i = 0; i < 10; i++)
    {
        t->white3.uid.uid[i] = 3;
    }
    for(i = 0; i < 10; i++)
    {
        t->white4.uid.uid[i] = 4;
    }
    for(i = 0; i < 10; i++)
    {
        t->white5.uid.uid[i] = 5;
    }
    for(i = 0; i < 10; i++)
    {
        t->white6.uid.uid[i] = 6;
    }
    for(i = 0; i < 10; i++)
    {
        t->white7.uid.uid[i] = 7;
    }
    for(i = 0; i < 10; i++)
    {
        t->white8.uid.uid[i] = 8;
    }
    for(i = 0; i < 10; i++)
    {
        t->white9.uid.uid[i] = 9;
    }
    for(i = 0; i < 10; i++)
    {
        t->black.uid.uid[i] = 0;
    }
    for(i = 0; i < 10; i++)
    {
        t->white55.uid.uid[i] = 5;
    }

   
    

    WL_add(t->white1);
    LOG("burasi pos cikmali");
    WL_search(t->white1.uid);
    WL_delete(t->white1.uid);
    LOG("burasi -1 cikmali");
    WL_search(t->white1.uid);
    WL_add(t->white1);

    for( i = 0; i < 36; i++)
    {
        for(u8 j = 0; j < 10; j++)
        {
            t->white[i].uid.uid[j] = rand() % 9;
        }
        WL_add(t->white[i]);
    }

    //WL_add(black);

    WL_add(t->white2);
    WL_search(t->white2.uid);

    for( i = 0; i < 36; i++)
    {

        for(u8 j = 0; j < 10; j++)
        {

            t->white[i].uid.uid[j] = rand() % 9;
        }
        WL_add(t->white[i]);
    }

  
    WL_add(t->white5);
    WL_delete(t->white5.uid);
    Serial.println("-1 cıkmali:");
    WL_search(t->white5.uid);
    WL_add(t->white3);

    //WL_add(white5);
    //WL_add(white55);

    for(u8 i = 0; i < 36; i++)
    {
        for(u8 j = 0; j < 10; j++)
        {
            t->white[i].uid.uid[j] = rand() % 9;
        }
        WL_add(t->white[i]);
    }


    WL_add(t->white5);
    WL_add(t->white6);
    WL_add(t->white7);
    WL_add(t->white8);
    WL_delete(t->white5.uid);
    WL_delete(t->white6.uid);

    //WL_delete(t->white1.uid);
    LOG("-1 cikmali: ");
    WL_search(t->white1.uid);
    LOG("pos cikmali: ");
    WL_search(t->white3.uid);

    for(u8 i = 0; i < 36; i++)
    {
        for(u8 j = 0; j < 10; j++)
        {
            t->white[i].uid.uid[j] = rand() % 9;
        }
        WL_add(t->white[i]);
    }

    WL_add(t->white9);

    WL_item_t *itemptr;
    WL_item_t item;
    itemptr=&item;

    WL_read(0,itemptr);
    Serial.printf("%s\n", itemptr->detail.name);
    
    

    /*
*/
    free(t);
}
>>>>>>> Stashed changes

