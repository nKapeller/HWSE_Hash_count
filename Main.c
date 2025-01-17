#include "ft_utils.h"
#include "ft_fileHandler.h"
#include "ft_filterUtils.h"
#include "ft_print.h"

#include <stdio.h>

/**
 * @brief
 * Main function mainly calls all other functions
 * in the right order and processes them
 *
 * @param argc      Count of the command line Arguments
 * @param argv      Value of the command line Arguments
 * @return int      Return status
 */

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("\n>>> Missing option and input filename as parameters, please enter: ./executable -f <FILENAME> <<<\n");
        return 1;
    }

    const char *inputFilename = ft_getFileName(argc, argv);
    const char *outputFilename = "filterd_output_text.txt";
    const char *binaryFilename = "binary_file.bin";

    if (!inputFilename)
    {
        return 1;
    }

    HashTable_t *table = ft_createHashTable();

    if (!table)
    {
        return 1;
    }

    ft_readAndProcessFile(inputFilename, table);

    ft_printTable(table);

    ft_printSelectedBucket(table);

    ft_executeBucketFilter(table, inputFilename, outputFilename);

    ft_printHashToBinary(table, binaryFilename);

    ft_freeHashTable(table);

    return 0;
}