#include <whitelist.h>
#include <FileSystem.h>
#include <tools.h>
#include "DebugLog.h"

// TODO : debuglog implementasyonu
#define CRCUID 0xDEAD
#define MAX_ITEM_SIZE 250
#define MAX_ITEMS_IN_FILE 50
#define MAX_FILENAME_LENGTH 15

#define MAX_UID_SIZE (MAX_ITEMS_IN_FILE * sizeof(UID_t))
#define MAX_DETAILS_SIZE (MAX_ITEMS_IN_FILE * sizeof(WL_Detail_t))
#define MAX_FILE_NUMBER (MAX_ITEM_SIZE / MAX_ITEMS_IN_FILE)

#define ERR_NO_SPACE 0xFF
#define WL_FileExtension ".wl"
#define Filename_crcuid "crcuid"
#define Filename_uid "uid"
#define Filename_detail "detail"

typedef enum
{
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
            p = pstrcpy(p, Filename_detail);
            *p++ = '0' + index;
            *p++ = NULL;
            break;
    }
    p = pstrcpy(p, WL_FileExtension);
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
        p = (u8 *)malloc(size);
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
    }

    return ret;
}

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
    memset((u8 *)&crcuid_list, 0, sizeof(crcuid_list));
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
                    if(0 == memcmp(&uid, &ruid, sizeof(UID_t)))
                    {
                        ret = i;
                        //LOG("[WL] add - find in: ");
                        //LOG(fn);
                        LOGd("[WL] add - position: ", pos);
                        //Serial.printf("[WL]-> search-> find in: %s\n", fn);
                        //Serial.printf("[WL]-> search-> position: %d\n", pos);
                        break;
                    }
                }
            }
        }
    }

    return ret;
}

//! Deletes given uid from whitelist (not only uid includes name surname and crc)
/*!
    \param uid [input] : the uid which will be deleted
    \return : boolean, true if successful
*/
bool WL_delete(UID_t uid)
{

    bool ret = false;
    u8 control = 0;
    u16 crc;
    UID_t ruid;
    WL_detail_t rdetail;
    u8 fileindex; // 0 ile 5 arasında değer döner
    long itempos; //dosyanın başından itibaren byte bazında pozisyon döner
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
            }
        }
        ///////////////////////////////////////////////////

        itempos = (pos % MAX_ITEMS_IN_FILE) * sizeof(WL_detail_t);
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

    if(3 == control)
    {
        ret = true;
    }
    LOGi("[WL]-> delete-> status: ", ret);

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

    WL_delete(item.uid); //

    lastfileindex = WL_getLastFileIndex();
    if(MAX_FILE_NUMBER > lastfileindex)
    {
        crc = CRC16(CRCUID, (u8 *)&item.uid, sizeof(UID_t));
        LOGi("[WL]-> add-> added crc: ", crc); // TODO pos ve crc değerleri çok büyük oldugu için u32 bastırabilecek bir debug log fonksiyonu
        //Serial.println(crc);

        WL_GetFileName(fn_CRCUID_List, 0, fn);
        if(false != FILE_Append(fn, &crc, sizeof(u16)))
        {
            Serial.printf("sizeof crc file: %d\n", FILE_get_size(fn));
            WL_GetFileName(fn_UID_List, lastfileindex, fn);
            if(false != FILE_Append(fn, &item.uid, sizeof(UID_t)))
            {
                Serial.printf("sizeof uid file: %d\n", FILE_get_size(fn));
                WL_GetFileName(fn_Detail_List, lastfileindex, fn);
                if(false != FILE_Append(fn, &item.detail, sizeof(WL_detail_t)))
                {
                    Serial.printf("sizeof detail file: %d\n", FILE_get_size(fn));
                    ret = true;
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
    bool ret = false;
    UID_t ruid;
    WL_detail_t rdetail;
    u32 itempos;
    u8 fileindex = WL_getFileIndex(index);
    char fn[MAX_FILENAME_LENGTH];

    itempos = (index % MAX_ITEMS_IN_FILE) * sizeof(UID_t);
    WL_GetFileName(fn_UID_List, fileindex, fn);

    if(false != FILE_Read(fn, &ruid, sizeof(UID_t), itempos))
    {
        memcpy(&item->uid, &ruid, sizeof(UID_t));

        itempos = (index % MAX_ITEMS_IN_FILE) * sizeof(WL_detail_t);

        WL_GetFileName(fn_Detail_List, fileindex, fn);

        if(false != FILE_Read(fn, &rdetail, sizeof(WL_detail_t), itempos))
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

    for(index = 0; index < MAX_FILE_NUMBER; index++)
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
    } t_t;

    t_t *t = (t_t *)malloc(sizeof(t_t));

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

    for(i = 0; i < 36; i++)
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

    for(i = 0; i < 36; i++)
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
    itemptr = &item;

    WL_read(0, itemptr);
    Serial.printf("%s\n", itemptr->detail.name);

    /*
    */
    free(t);
}
