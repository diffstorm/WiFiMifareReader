#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "types.h"
#include <FS.h>
#include <WString.h>

extern bool FILE_Init();

//! Write data to a file (an internal function for fail safe structure)
/*!
    \param f [output] : file pointer -> written in to this file
    \param context [input] : the data which will be written
    \param length [input] : how many bytes data will be written
    \return : boolean, true if successful
*/
extern bool FILE_write_internal(File *f, void *context, u32 length);

//! Read context from a file (an internal function for fail safe structure)
/*!
    \param f [input] : file pointer -> which data will be read from
    \param context [output] : read in to context
    \param length [input] : how many bytes data will be read
    \return : boolean, true if successful
*/
extern bool FILE_read_internal(File *f, void *context, u32 length);

//! Append data to a file (this will add data to end of the file)
/*!
    \param name [output] : file name which the data will be added in
    \param context [input] : the data which will be added
    \param length [input] : how many bytes data will be written
    \return : boolean, true if successful
*/
extern bool FILE_Append(char *name, void *context, u32 length);

//! Write context to a file (this will delete all data in the given file and add given length of data)
/*!
    \param name [output] : file name which the data will be written in
    \param context [input] : the data which will be written
    \param length [input] : how many bytes data will be written
    \return : boolean, true if successful
*/
extern bool FILE_Write(char *name, void *context, u32 length);


//! Read data from the file from given position
/*!
    \param name [input] : file name which the data will be read
    \param context [output] : Read in to context
    \param length [input] : how many bytes data will be read
    \param pos [input] : beginning position of the read process in file
    \return : boolean, true if successful
*/
extern bool FILE_Read(char *name, void *context, u32 lenght, u32 pos);

//! Updates a file from given position
/*!
    \param name [output] : file name which the data will be written
    \param context [input] : the data which will be written
    \param length [input] : how many bytes data will be written
    \param pos [input] : beginning position of the write process in file
    \return : boolean, true if successful
*/
extern bool FILE_update(char *name, void *context, u32 length, u32 pos);

//! Gives all filenames in root directory
/*!
    \return : string, filenames seperated with comma in a string
*/
extern String FILE_get_file_list();


extern size_t FILE_get_dir_size(char *dir);

extern size_t FILE_system_available_size();

extern bool FILE_delete(char *name);

extern bool FILE_IsExists(char *name);

extern size_t FILE_get_size(char *name);

#endif // __FILESYSTEM_H__