#include <filesystem.h>

void File_Init()
{
    if (SPIFFS.begin())
    {
        Serial.println("SPIFSS begin...");
        SPIFFS.format();
    }
    else
    {
        Serial.print("SPISS not begin...");
    }
}

size_t File_Write(char *name, void *context, u32 length)
{
    File f = SPIFFS.open(name, "a");
    if (NULL != f)
    {
        f.write((u8 *)context, length);
        f.close();
    }
    else
    {
        Serial.println("dosya acilamadi");
    }
}

size_t File_Read(char *name, void *context, u32 lenght)
{
    u32 pos = 0;
    u32 len = 0;
    File f = SPIFFS.open(name, "r");
    if (NULL != f)
    {
        if (0 == strcmp(name, FILENAME(WHITELIST))
        {
            len = (lenght) / (sizeof(whitelist_t));
            whitelist_t *whitelist = (whitelist_t *)context;
            for (size_t i = 0; i < len; i++)
            {
                f.seek(pos, SeekMode::SeekSet);
                f.read((u8 *)whitelist, sizeof(whitelist_t));
                pos += sizeof(whitelist_t);
            }
        }
        if (0 == strcmp(name, FILENAME(LOG)))
        {
            len = (lenght) / (sizeof(log_info_t));
            log_info_t *loginfo = (log_info_t *)context;
            for (size_t i = 0; i < len; i++)
            {
                f.seek(pos, SeekMode::SeekSet);
                f.read((u8 *)loginfo, sizeof(log_info_t));
                pos += sizeof(log_info_t);
            }
        }
    }
    else
    {
        Serial.println("dosya acilamadi");
    }
}

void File_delete_File(const char *name)
{
    File f = SPIFFS.open(name,"r+");
    if(NULL != name)
    {
        if(0!= SPIFFS.remove(name))
        {
            Serial.printf("Belirtilen %s dosyası silindi\n",name);
        }
    }
    else
    {
        Serial.printf("Belirtilen %s dosyası bulunamadı\n",name);
    }
}

size_t File_get_rowCount(char* name,void* context)
{
     File f= SPIFFS.open(name,"r");
    if(NULL != f)
    {
        if(0 == strcmp(name,FILENAME(WHITELIST)))
        {
            return f.size() / (sizeof(whitelist_t));
        }
        if(0 == strcmp(name,FILENAME(LOG)))
        {
            return f.size() / (sizeof(log_info_t));
        }
    }
    else
    {
        return -1;
    }
}

void File_get_List()
{
    Dir dir;
    dir = SPIFFS.openDir("/");
    while(dir.next())
    {
        Serial.println(dir.fileName().substring(1));
    }
}

size_t File_check_size(const char *name)
{
    File f= SPIFFS.open(name,"r");
    if(NULL != f)
    {
        return f.size();
    }
    else
    {
        Serial.printf("belirtilen %s dosyasi bulunamadı",name);
    }
    
}