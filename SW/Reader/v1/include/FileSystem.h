
#ifndef _filesystem_H_
#define _filesystem_H_
#include <FS.h>

//File Names
#define ROOT /
#define LOG /log
#define WHITELIST /whitelist

//expanding macro into string
#define STR_EXPAND(tok) #tok
#define FILENAME(str) STR_EXPAND(str)


void File_Init();

size_t File_Write(char *name, void *context, u32 length);

size_t File_Read(char *name,void* context,u32 lenght);

bool File_IsExists(char *name);

size_t File_check_size(const char *filename);

void File_delete_File(const char *filename);

void File_get_List();

size_t File_get_rowCount(char* name,void* context);

void File_record_display(char* name,void* context,uint32_t size);

#endif