#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__
#include <FS.h>

bool FILE_create(char* name);

bool FILE_Init();

bool FILE_write_internal(File *f, void *context, u32 length);

bool FILE_read_internal(File *f, void *context, u32 length);

bool FILE_Write(char *name, void *context, u32 length);

bool FILE_Read(char *name,void *context,u32 lenght, u32 pos);

bool FILE_Append(char *name, void *context, u32 length);

bool FILE_IsExists(char *name);

size_t FILE_check_size( char *name);

bool FILE_delete( char *name);

void FILE_get_List();

bool FILE_rename(char* name,char* name1);

bool FILE_update(char *name,void* context,u32 length,u32 pos);

size_t FILE_dir_size(char* dir);



#endif