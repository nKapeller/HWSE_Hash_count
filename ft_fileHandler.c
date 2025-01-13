#include "ft_fileHandler.h"
#include "ft_structs.h"
#include "ft_hashTable.h"

#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/getopt_core.h>

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
            printf("test of optarg: %s: ", filename);
            break;
        default:
            fprintf(stderr, "Please enter -> -f <FILENAME> after ./executable\n");
            return NULL;
        }

        if (!filename)
        {
            fprintf(stderr, "Please enter -> -f <FILENAME> after ./executable\n");
        }
    }
    return filename;
}

FILE *ft_openFile(char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        fprintf(stderr, "Faild to open file");
        return NULL;
    }
    return file;
}

void ft_readAndProcessFile(FILE *file, HashTable_t *table)
{
    size_t lenght = 0;
    char *line = NULL;

    const char *delimiters = " .\n;:,?\t"; // all wordseperators

    while (getline(&line, &lenght, file) != -1) // -1 is return of getline when error or end of file
    {
        char *token = strtok(line, delimiters); // strtok takes line and seperates first word

        while (token)
        {
            ft_insertNewNode(table, token);
            token = strtok(NULL, delimiters); // then moves on to next word as long as token is not NULL
        }
    }
    free(line);
}