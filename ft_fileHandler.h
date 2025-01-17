#ifndef FT_FILEHANDLER_H
#define FT_FILEHANDLER_H

#include "ft_fileHandler.h"
#include "ft_structs.h"
#include "ft_hashTable.h"

#include <stdio.h>

FILE *ft_openFile(const char *filename);
const char *ft_getFileName(int argc, char *argv[]);
void ft_readAndProcessFile(const char *inputFilename, HashTable_t *table);

#endif