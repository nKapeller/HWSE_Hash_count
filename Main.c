#include "ft_utils.h"
#include "ft_fileHandler.h"
#include "ft_filterUtils.h"
#include "ft_print.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\n>>> Missing option and input filename as parameters, please enter: ./executable -f <FILENAME> <<<\n");
    }

    const char *inputFilename = ft_getFileName(argc, argv);
    const char *outputFilename = "filterd_output_text.txt";

    if (!inputFilename)
    {
        return 1;
    }

    FILE *file = ft_openFile(inputFilename);

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

    ft_executeBucketFilter(table, inputFilename, outputFilename);

    ft_freeHashTable(table);

    return 0;
}