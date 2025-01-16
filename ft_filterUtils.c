#define _POSIX_C_SOURCE 200809L

#include "ft_fileHandler.h"
#include "ft_structs.h"
#include "ft_hashTable.h"
#include "ft_utils.h"
#include "ft_filterUtils.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int ft_parseBucketIndizes(char *inputStr, int *selectedBucketsArray)
{
    char *delimiter = " .;:,\t";
    char *token = strtok(inputStr, delimiter);
    int count = 0;

    while (token)
    {
        long long bucketIndex = strtoll(token, NULL, 10);

        if (bucketIndex >= 0 && bucketIndex < TABLE_SIZE)
        {
            selectedBucketsArray[count] = (int)bucketIndex; // safe my index in the Array
            count++;
        }
        else
        {
            fprintf(stderr, "Error: invalid index, skipping this step --parseBucketIndizes()--\n");
        }
        token = strtok(NULL, delimiter);
    }
    return count;
}

int ft_isBucketSelected(int hashValue, const int *selectedBucket, int count)
{
    int i = 0;

    while (i < count)
    {
        if (hashValue == selectedBucket[i])
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int ft_isWordInBucket(HashTable_t *table, int bucketIndex, const char *word)
{
    Node_t *current = table->bucket[bucketIndex];

    while (current)
    {
        if (strcmp(current->keyString, word) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void ft_filterWordsByBucket(HashTable_t *table, FILE *outputFile, const char *line, int bucketCount, const int *selectedBuckets)
{
    if (!table || !line || !outputFile || !selectedBuckets)
    {
        fprintf(stderr, "Error: invlaid input! --ft_filterWordsByBucket()--\n");
        return;
    }

    char *lineCpy = ft_strdupCalloc(line);

    if (!lineCpy)
    {
        fprintf(stderr, "Error: allocation of line failed! --ft_filteWordsByBucket()--\n");
        return;
    }

    char *delimiter = " .;:,\t";
    char *token = strtok(lineCpy, delimiter);

    while (token)
    {
        int hashValue = ft_getHashValue(token);

        if (ft_isBucketSelected(hashValue, selectedBuckets, bucketCount))
        {
            if (ft_isWordInBucket(table, hashValue, token))
            {
                fprintf(outputFile, "%s", token);
            }
        }
        token = strtok(NULL, delimiter);
    }
    free(line);
}

void ft_processFileWithBuckets(FILE *inputFile, FILE *outputfile, HashTable_t *table, const int *selectedBuckets, int bucketCount)
{
    if (!inputFile || !outputfile || !table || !selectedBuckets)
    {
        fprintf(stderr, "Error: invalid input! --ft_processFileWithBuckets()--\n");
        return;
    }

    char *line = NULL;
    size_t lenght = 0;

    while (getline(&line, &lenght, inputFile) != -1)
    {
        ft_filterWordsByBucket(table, outputfile, line, bucketCount, selectedBuckets);
        fprintf(outputfile, "\n");
    }
    free(line);
}

void ft_executeBucketFilter(HashTable_t *table, const char *inputfileName, const char *outputFileName)
{
    if(!table || !inputfileName || !outputFileName)
    {
        fprintf(stderr, "Error: invalid input! --ft_executeBucketFilter()--\n");
        return;
    }

    char input[MAX_INDEX_NUMBER_LENGHT];

    printf("Please enter one or more bucket indices you want to filter.\nYour numbers will be seperated by 'space' '.' ';' ': ',' or tab\n");

    if(!ft_readInput(input, sizeof(input)))
    {
        return;
    }

    int selectedBuckets[TABLE_SIZE] = {0};
    int bucketCount = ft_parseBucketIndizes(input, selectedBuckets);

    if(bucketCount == 0)
    {
        fprintf(stderr, "Sorry, invalid Buckest selected!\n");
        return;
    }

    FILE *inputFile = fopen(inputfileName, "r");

    if(!inputFile)
    {
        fprintf(stderr, "Error: failed to open input file! --ft_executeBucketFilter()--\n");
        return;
    }

    FILE *outputFile = fopen(outputFileName, "w");

    if(!outputFile)
    {
        fclose(inputFile);
        fprintf(stderr, "Error: failed to open output file! --ft_executeBucketFilter()--\n");
        return;
    }

    ft_processFileWithBuckets(inputFile, outputFile, table, selectedBuckets, bucketCount);

    printf("Filterd text written to file: %s\n", outputFileName);

    fclose(inputFile);
    fclose(outputFile);
}