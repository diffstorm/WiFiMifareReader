#include <FileSystem.h>


bool File_Init()
{
    bool ret=false;
    if (SPIFFS.begin())
    {
        ret=false;
    }
    else
    {
        ret=true;
    }
    return ret;
}


bool File_Append(char *name, void *context, u32 length)
{
   
    bool ret=false;
    File f = SPIFFS.open(name, "a");   
    if (NULL != f)
    {
        
        
        f.write((u8 *)context, length);
        f.close();
        ret=true;
    }
    else
    {
        ret=false;
    }
    return ret;
}

bool File_Write(char *name, void *context, u32 length)
{
   
    bool ret=false;
    File f = SPIFFS.open(name, "w");
    
    if (NULL != f)
    {
        f.write((u8 *)context, length);
        f.close();
        ret=true;
    }
    else
    {
        ret=false;
    }
    return ret;
}

bool File_rename(char* name,char* name1)
{
    return SPIFFS.rename(name, name1);     
}

bool File_Read(char* name,void* context,u32 length,u32 pos)
{
    bool ret=false;
    File f = SPIFFS.open(name, "r");
    if(!f)
    {
        ret=false;
    }

    else
    {
        
        f.seek(pos, SeekMode::SeekSet);
        f.read((u8*)context,length);
        f.close();
        ret=true;
    }
    return ret;
    
}  

bool File_update(char *name,void* context, u32 length,u32 pos)
{
    bool ret=false;
    File f = SPIFFS.open(name, "r+");
    if(!f)
    {
        ret=false;
    }

    else
    {
        

        f.seek(((f.size()-length)),SeekMode::SeekSet);  //(f.size()-length)

        f.read((uint8_t*)context,length);
        f.seek(pos*length,SeekMode::SeekSet); 
        f.write((u8*)context,length); 
        //bool a=f.truncate(f.size()-length);
        f.close();
        ret=true;
    }   
    return ret;
}



bool File_IsExists(char *name)
{
    return SPIFFS.exists(name);
}

size_t File_check_size( char *filename)
{
    File f =SPIFFS.open(filename,"r");
    return f.size();
}

bool File_delete_File( char *filename)
{
    bool ret=true;
    if (0 != SPIFFS.remove(filename))
    {
        ret=false;
    }
    else
    {
        ret=true;
    }
    return ret;
}


void File_get_List()
{
    String path="/";
    Dir dir =  SPIFFS.openDir(path);
    String output = "[";
    while (dir.next())
    {
       File entry = dir.openFile("r");
       if(output !="[")
       {
           output+= ",";
       }
       output+=String(entry.name()).substring(1);       //entry.name() --> /test veriyor. / işaretini atmak için substring kullanıyoruz.
       entry.close();
    }
    output+="]"; 
    Serial.println(output);
}