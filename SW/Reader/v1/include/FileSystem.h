#ifndef filesystem_H
#define filesystem_H
#include <FS.h>



bool File_Init();

bool File_Write(char *name, void *context, u32 length);

bool File_Read(char *name,void *context,u32 lenght, u32 pos);

bool File_Append(char *name, void *context, u32 length);

bool File_Remove(char *name);

bool File_IsExists(char *name);

size_t File_check_size( char *filename);

bool File_delete_File( char *filename);

void File_get_List();

bool File_rename(char* name,char* name1);

bool File_update(char *name,void* context,u32 length,u32 pos);

#endif
