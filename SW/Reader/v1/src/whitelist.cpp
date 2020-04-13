#include <whitelist.h>
#include<FileSystem.h>
#include<tools.h>

#define CRCUID 0xDEAD

char *uidFile = "/uid";
char *crcUid ="/crcUid";
char *names="/names";
char *tempFile="/temp";
char *tempFile2="/temp2";


u16 crcBuf[250];
u16 buf[1];

void WH_add(whitelist_t wl)
{
    u16 crc;
    File_Append(uidFile,&wl,(u32)wl.uid.length);
    crc= CRC16(CRCUID, (u8 *)wl.uid.uid, (unsigned int)wl.uid.length);

    File_Append(crcUid,&crc,sizeof(crc));
    File_Append(names,&wl.name,sizeof(wl.name));
    File_Append(names,&wl.surname,sizeof(wl.surname));       
}

bool WH_searchUID(byte uid[],size_t len)
{
    bool ret=false;
    u16 crc1;
    u32 pos=0;
    crc1= CRC16(CRCUID, (u8 *)uid, (unsigned int)len);

    whitelist_t wl;
    File_Read(crcUid,&crcBuf,File_check_size(crcUid),0); //File_check_size(crcUid)


    for(size_t i=0;i<File_check_size(crcUid)/sizeof(u16);i++)
    {
        
         if(crcBuf[i]==crc1)
            {    
                pos=i*sizeof(wl.uid.uid);
                File_Read(uidFile,&wl,wl.uid.length,pos);
                if(0==memcmp(wl.uid.uid,uid,wl.uid.length))
                {
                    ret=true;
                    break;
                }
            } 
    }
    
    return ret;        
        
}



bool WH_delete(byte uid[],size_t len)
{

    bool ret=false;
    u16 crc1;
    u32 pos=0;

    crc1= CRC16(CRCUID, (u8 *)uid, (unsigned int)len);

    whitelist_t wl;
    File_Read(crcUid,&crcBuf,File_check_size(crcUid),0);


    for(size_t i=0;i<File_check_size(crcUid)/sizeof(u16);i++)
    {
        
         if(crcBuf[i]==crc1)
            {
                
                
                pos=i*sizeof(wl.uid.uid);
                File_Read(uidFile,&wl,wl.uid.length,pos);
                if(0==memcmp(wl.uid.uid,uid,wl.uid.length))
                {
                    pos=i;
                    File_update(crcUid,&buf,sizeof(buf),pos);
                    File_Read(crcUid,&crcBuf,File_check_size(crcUid)-sizeof(u16),0);
                    File_Write(crcUid,&crcBuf,File_check_size(crcUid)-sizeof(u16));
                    Serial.print("crc file size: ");
                    Serial.println(File_check_size(crcUid));
                    File_Read(crcUid,&crcBuf,File_check_size(crcUid),0);
                    ///////////////////////////////////////
                    pos=i*sizeof(wl.uid.uid);
                    File_update(uidFile,&wl,wl.uid.length,pos);   //TODO dosya boyutu kesilecek
                    //File_Read(uidFile,&tempFile,File_check_size(uidFile)-wl.uid.length,0);
                    //File_delete_File(uidFile);
                    //File_rename(tempFile,uidFile);
                    //////////////////////////////////////////
                    pos=i*(sizeof(wl.name)+sizeof(wl.surname));   // TODO dosya boyutu kesilecek
                    File_update(names,&wl,(sizeof(wl.name)+sizeof(wl.surname)),pos);
                    //File_Read(names,&tempFile2,File_check_size(names)-(sizeof(wl.name)+sizeof(wl.surname)),0);
                    //File_delete_File(names);
                    //File_rename(tempFile2,names);
                    ret=true;
                break;
                }
            } 

    }
    return ret;
    


}


                   