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
        SPIFFS.format();      //ESP reset attığında düzelme ihtimaline karşı, format kullanılmasa olur mu? 
        ESP.restart();        //Çünkü dosyalar kaybedilecek. Ya da güncel dosyalar bir yerde saklanacak ve cihaza geri göderilecek mi?
    }

    return ret;    
}


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

bool FILE_read_internal(File *f, void *context, u32 length)
{
    u32 offset = 0;
    u32 read = 0;
    u8 error = 3;
    
    while(offset < length && error > 0)
    {
        read = f->read((u8 *)context + offset , length - offset);  //

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

bool FILE_create(char* name)
{
    bool ret=false;

    File f = SPIFFS.open(name,"r+");

    if(NULL != f)
    {
        ret=true;
        f.close();
    }

    return f;
}


bool FILE_Append(char *name, void *context, u32 length)
{

    bool ret = false;

    File f = SPIFFS.open(name, "a");

    if(NULL != f)
    {
        if(true==FILE_write_internal(&f, context, length))    
        {
            ret = true;
        }

        f.close(); 
    }

    return ret;
}

bool FILE_Write(char *name, void *context, u32 length)
{

    bool ret = false;

    File f = SPIFFS.open(name, "w");

    if(NULL != f)
    {
        if(true==FILE_write_internal(&f, context, length))
        {
            ret = true; 
        }

        f.close(); 
    }

    return ret;
}

bool FILE_rename(char *name, char *name1)
{
    return SPIFFS.rename(name, name1);
}

bool FILE_Read(char *name, void *context, u32 length, u32 pos)
{

    bool ret = false;

    File f = SPIFFS.open(name, "r");

    if(NULL != f)
    {
        Serial.println("dosya acildi");
        if(true==f.seek(pos, SeekMode::SeekSet))
        {
            Serial.println("seek valisti");
            if(true==FILE_read_internal(&f, context, length))
            {
                //f.read((u8 *)context,length);
                Serial.println("readint calisti");
                ret=true;
            }
        } 

        f.close();
        Serial.printf("ret: %d",ret);     
    }

    return ret;

}


bool FILE_update(char *name, void *context, u32 length, u32 pos)
{
    bool ret = false;

    File f = SPIFFS.open(name, "r+");

    if(NULL != f)
    {

        if(true==f.seek((f.size() - length),SeekMode::SeekSet))
        {
            if(true==FILE_read_internal(&f, context, length))
            {
                if(true==f.seek(pos*length, SeekMode::SeekSet))
                {
                    if(true==FILE_write_internal(&f, context,length))
                    {
                        ret=true;
                    }
                }
            }
        }

    //bool a=FILE_truncate(name, (f.size()-length));

    f.close();  
    }

    return ret;
}



bool FILE_IsExists(char *name)
{
    return SPIFFS.exists(name);
}

size_t FILE_check_size(char *name)
{
    File f = SPIFFS.open(name, "r");
    return f.size();
}

bool FILE_delete(char *name)
{
    bool ret = false;

    if(true == SPIFFS.remove(name))
    {
        ret = true;
    }
    
    return ret;
}


void FILE_get_List()
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
        output += String(entry.name()).substring(1);     //entry.name() --> /test veriyor. / işaretini atmak için substring kullanıyoruz.
        entry.close();
    }
    output += "]";
    Serial.println(output);
}

size_t FILE_dir_size(char* dirPath)
{
    size_t size=0;

    Dir dir = SPIFFS.openDir(dirPath);
    
    while (dir.next())
    {
      size += dir.fileSize();  
    }

    return size;
}