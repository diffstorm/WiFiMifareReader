#include <filesystem.h>


bool FILE_Init()
{
    bool ret=false;
    u8 i;
    u8 error = 100;
    u8 errorTop=error+30;

    SPIFFS.format();   // silinecek. Deneme amaçlı dosya boyutları artmasın diye yapıldı.

    for(i = 0; i <= error; i++)
    {
        if(false == SPIFFS.begin())
        {
            delay(50);
        }
        else
        {
            ret=true;
            break;
        }
    }

    if(false==ret)
    {
        while(i >= error && i <= errorTop)
        {
            if(false == SPIFFS.begin())
            {
                SPIFFS.check();
                SPIFFS.gc(); 
            }
            else
            {
                ret=true;
                break;
            }

        i++; 
        }
    }

    if(i > errorTop)
    {
        SPIFFS.format();      
        ESP.restart();        
    }

    return ret;    
}

//! Write data to a file (an internal function for fail safe structure)
/*!
    \param f [output] : file pointer -> written in to this file
    \param context [input] : the data which will be written
    \param length [input] : how many bytes data will be written
    \return : boolean, true if successful
*/
bool FILE_write_internal(File *f, void *context, u32 length)
{
    u32 offset = 0;
    u32 written = 0;
    u8 error = 3;

    while(offset < length && error > 0)
    {
        written = f->write((u8 *)context + offset, length - offset);
        
        if(written > 0)
        {
            offset += written;
        }
        else
        {
            error--;
        }
    }

    return (offset == length);
}

//! Read context from a file (an internal function for fail safe structure)
/*!
    \param f [input] : file pointer -> which data will be read from
    \param context [output] : read data in to context 
    \param length [input] : how many bytes data will be read
    \return : boolean, true if successfula
*/
bool FILE_read_internal(File *f, void *context, u32 length)
{
    u32 offset = 0;
    u32 read = 0;
    u8 error = 3;
    
    while(offset < length && error > 0)
    {
        read = f->read((u8 *)context + offset , length - offset);  

        if(read > 0)
        {
            offset += read;
        }
        else
        {
            error--;
        }
    }

    return (offset == length);    
}


//! Append data to a file (this will add data to end of the file)
/*!
    \param name [input] : file name which the data will be added in
    \param context [input] : the data which will be added
    \param length [input] : how many bytes data will be written
    \return : boolean, true if successful
*/
bool FILE_Append(char *name, void *context, u32 length)
{

    bool ret = false;

    File f = SPIFFS.open(name, "a");

    if(NULL != f)
    {
        if(false != FILE_write_internal(&f, context, length))    
        {
            ret = true;
        }

        f.close(); 
    }

    return ret;
}

//! Write context to a file (this will delete all data in the given file and add given length of data)
/*!
    \param name [output] : file name which the data will be written in
    \param context [input] : the data which will be written
    \param length [input] : how many bytes data will be written
    \return : boolean, true if successful
*/
bool FILE_Write(char *name, void *context, u32 length)
{

    bool ret = false;

    File f = SPIFFS.open(name, "w");

    if(NULL != f)
    {
        if(false != FILE_write_internal(&f, context, length))
        {
            ret = true; 
        }

        f.close(); 
    }

    return ret;
}


//! Read data from the file from given position 
/*!
    \param name [input] : file name which the data will be read from
    \param context [output] : Read in to context
    \param length [input] : how many bytes data will be read
    \param pos [input] : beginning position of the read process in file  
    \return : boolean, true if successful
*/
bool FILE_Read(char *name, void *context, u32 length, u32 pos)
{

    bool ret = false;

    File f = SPIFFS.open(name, "r");

    if(NULL != f)
    {
        
        if(false != f.seek(pos, SeekMode::SeekSet))
        {
            
            if(false != FILE_read_internal(&f, context, length))
            {
                ret=true;
            }
        } 

        f.close();    
    }

    return ret;

}

//! Updates a file from given position
/*!
    \param name [output] : file name which the data will be written
    \param context [input] : the data which will be written
    \param length [input] : how many bytes data will be written
    \param pos [input] : beginning position of the write process in file  
    \return : boolean, true if successful
*/
bool FILE_update(char *name, void *context, u32 length, u32 pos)
{
    bool ret = false;

    File f = SPIFFS.open(name, "r+");
    
    if(NULL != f)
    {

        if(false != f.seek(pos, SeekMode::SeekSet))
        {
            if(false != FILE_write_internal(&f, context,length))
            {
                ret=true;
            }
        }

    f.close();  
    }

    return ret;
}


//! Gives all filenames in "/" directory 
/*!
    \return : string, filenames seperated with comma in a string
*/
String FILE_get_file_list()
{
    String path = "/";
    Dir dir =  SPIFFS.openDir(path);
    String output = "[";
    while(dir.next())
    {
        File entry = dir.openFile("r");
        if(output != "[")
        {
            output += ",";
        }
        output += String(entry.fullName());    //name()).substring(1); //name ile fullname aynı sonucu veriyor
        entry.close();
    }

    output += "]";
    return output;
}

size_t FILE_get_dir_size(char* dirPath)
{
    size_t size=0;

    Dir dir = SPIFFS.openDir(dirPath);
    while (dir.next())
    {
      size += dir.fileSize();  
    }

    return size;
}

size_t FILE_system_available_size()
{
    FSInfo FSInfo;
    size_t available = 0;

    if(false != SPIFFS.info(FSInfo))
    {
        available = FSInfo.totalBytes - FSInfo.usedBytes;
    }

    return available;
}

bool FILE_delete(char *name)
{
    return SPIFFS.remove(name);
}

bool FILE_IsExists(char *name)
{
    return SPIFFS.exists(name);
}

size_t FILE_get_size(char *name)
{
    File f = SPIFFS.open(name, "r");
    size_t ret = f.size();
    f.close();
    return ret;
}
