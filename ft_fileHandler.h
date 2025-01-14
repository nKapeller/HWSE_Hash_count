#ifndef FT_FILEHANDLER_H
#define FT_FILEHANDLER_H

#include "ft_fileHandler.h"
#include "ft_structs.h"
#include "ft_hashTable.h"

#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/getopt_core.h>

const char *ft_getFileName(int argc, char *argv[]);
FILE *ft_openFile(const char *filename);
void ft_readAndProcessFile(FILE *file, HashTable_t *table);

#endif