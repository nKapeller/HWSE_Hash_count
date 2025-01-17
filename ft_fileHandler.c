#define _POSIX_C_SOURCE 200809L // getline

#include "ft_fileHandler.h"
#include "ft_structs.h"
#include "ft_hashTable.h"

#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/getopt_core.h>

/**
 * @brief
 * function to parse command line arguments, with the -f flag
 * it looks for filenames as long as there are no more options
 * then it will return -1
 *
 * @param argc count of command line arguments
 * @param argv value of command line argument
 *
 * @return const char*  srting of the filename provided in the command line
 */

const char *ft_getFileName(int argc, char *argv[])
{
    int opt = 0;
    const char *filename = NULL;

    while ((opt = getopt(argc, argv, "f:")) != -1)
    {
        switch (opt)
        {
        case 'f':
            filename = optarg;
            break;
        default:
            fprintf(stderr, "\n>>> Please enter: ./executable -f <FILENAME> <<<\n");
            return NULL;
        }
    }
    return filename;
}

/**
 * @brief
 * Function to open a strem to a read only file
 *
 * @param filename   string for the input filename
 * @return           FILE* pointer to rhe opend file
 */

FILE *ft_openFile(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        fprintf(stderr, "\n>>> Faild to open file or wrong file, please use .txt format <<<\n");
        return NULL;
    }
    return file;
}

/**
 * @brief
 *  Function to read line by line and with the help of strtok()
 *  seperates it word by word when given delimiter was found.
 *
 * @param fileName  Pointer to a file name to process the stream / have acces to it
 * @param table     Pointer to a struct to further process it / have acces to it
 */

void ft_readAndProcessFile(FILE *file, HashTable_t *table)
{
    if (!table)
    {
        fprintf(stderr, "Error: invalid input --ft_readAndProcessFile()\n");
        return;
    }

    size_t lenght = 0;
    char *line = NULL;

    const char *delimiters = " .\n;:,?\t";

    while (getline(&line, &lenght, file) != -1) 
    {
        char *token = strtok(line, delimiters); 

        while (token)
        {
            ft_insertNewNode(table, token);
            token = strtok(NULL, delimiters);
        }
    }
    free(line);
}