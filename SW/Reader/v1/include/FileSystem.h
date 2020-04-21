#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__
#include <FS.h>
#include <WString.h>


bool FILE_Init();

//! Append data to a file (this will add data to end of the file)
/*!
    \param name [output] : file name which the data will be added in
    \param context [input] : the data which will be added
    \param length [input] : how many bytes data will be written
    \return : boolean, true if successful
*/
bool FILE_Append(char *name, void *context, u32 length);

//! Write context to a file (this will delete all data in the given file and add given length of data)
/*!
    \param name [output] : file name which the data will be written in
    \param context [input] : the data which will be written
    \param length [input] : how many bytes data will be written
    \return : boolean, true if successful
*/
bool FILE_Write(char *name, void *context, u32 length);


//! Read data from the file from given position 
/*!
    \param name [input] : file name which the data will be read
    \param context [output] : Read in to context
    \param length [input] : how many bytes data will be read
    \param pos [input] : beginning position of the read process in file  
    \return : boolean, true if successful
*/
bool FILE_Read(char *name,void *context,u32 lenght, u32 pos);

//! Updates a file from given position 
/*!
    \param name [output] : file name which the data will be written
    \param context [input] : the data which will be written
    \param length [input] : how many bytes data will be written
    \param pos [input] : beginning position of the write process in file  
    \return : boolean, true if successful
*/
bool FILE_update(char *name,void* context,u32 length,u32 pos);

//! Gives all filenames in "/" directory 
/*!
    \return : string, filenames seperated with comma in a string
*/
String FILE_get_file_list();


size_t FILE_get_dir_size(char* dir);

size_t FILE_system_available_size();

bool FILE_delete( char *name);

bool FILE_IsExists(char *name);

size_t FILE_get_size( char *name);

#endif