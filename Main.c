#include "ft_utils.h"
#include "ft_fileHandler.h"
#include "ft_print.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\n>>> Missing option and filename as parameters, please enter: ./executable -f <FILENAME> <<<\n");
    }

    const char *filename = ft_getFileName(argc, argv);

    if (!filename)
    {
        return 1;
    }

    FILE *file = ft_openFile(filename);

    if (!file)
    {
        return 1;
    }

    HashTable_t *table = ft_createHashTable();

    if (!table)
    {
        return 1;
    }

    ft_readAndProcessFile(file, table);

    fclose(file);

    ft_printTable(table);

    printf("\n\n");

    ft_printSelectedBucket(table);

    ft_freeHashTable(table);

    return 0;
}