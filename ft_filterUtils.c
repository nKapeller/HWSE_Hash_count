#define _POSIX_C_SOURCE 200809L

#include "ft_fileHandler.h"
#include "ft_structs.h"
#include "ft_hashTable.h"
#include "ft_utils.h"
#include "ft_filterUtils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief 
 * Function to process the input string 
 * transforming it to an long long int and checking for valid indices  
 * then storing the count of valid indizes to an Array
 * 
 * @param inputStr          String to be processed
 * @param selectedBuckets   Array for storing valid indizes
 * @return int              Count of valid indices
 */

int ft_parseBucketIndizes(char *inputStr, int *selectedBuckets)
{

    char *delimiter = " .;:,\t";
    char *token = strtok(inputStr, delimiter);
    int count = 0;

    while (token)
    {
        long long bucketIndex = strtoll(token, NULL, 10);

        if (bucketIndex >= 0 && bucketIndex < TABLE_SIZE)
        {
            selectedBuckets[count] = (int)bucketIndex; 
            count++;
        }
        else
        {
            fprintf(stderr, "Warning: invalid index was found and ignored, every valid index was processed! --ft_parseBucketIndizes()--\n");
        }
        token = strtok(NULL, delimiter);
    }
    return count;
}

/**
 * @brief 
 * Function to check if a bucket is selected
 * helper for an other function
 * 
 * @param hashValue         Hashvalue that needs to be checked
 * @param selectedBucket    Pointer to Array with bucket indices
 * @param count             Count of valid buckets indices
 * @return int              return 0 if nothing was found and 1 if match was found
 */
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

/**
 * @brief 
 * Function to validate if a word is located in a specific bucket 
 * if it was found function returns 1 else 0
 * 
 * @param table            Pointer to Hashtable struct
 * @param bucketIndex      Index of bucket which shall be searched for word
 * @param word             Word to look for in bucket
 * @return int             return 1 if word was found and 0 if not
 */
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

/**
 * @brief 
 * Function takes a line of input and tokenizes it then process it
 * by looking for right bucket with help of the hashvalue
 * if it has found one it prints the word to the output file
 * 
 * @param table             Pointer to Hashtable struct
 * @param outputFile        File where matching words will be written to 
 * @param line              A line of the inputfile from other function
 * @param bucketCount       Amount of buckets to be looked at
 * @param selectedBuckets   Array of valid buckets 
 */

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
                fprintf(outputFile, "%s ", token);
            }
        }
        token = strtok(NULL, delimiter);
    }
    free(lineCpy);
}

/**
 * @brief 
 * Function to process the input file line by line
 * and is then printing the filtered words in an output file
 * 
 * @param inputFile         Pointer to input file 
 * @param outputfile        Pointer to output file
 * @param table             Pointer to hashtable struct 
 * @param selectedBuckets   Pointer to Array of buckets indices to be filtered
 * @param bucketCount       Amount of buckets to be looked at
 */

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

/**
 * @brief 
 * Function to execute the helper functions
 * here comes all together and will be processed
 * also handles the file stream
 * 
 * @param table             Pointer to hashtable struct 
 * @param inputfileName     Pointer to input file name
 * @param outputFileName    Pointer to output file name
 */

void ft_executeBucketFilter(HashTable_t *table, const char *inputfileName, const char *outputFileName)
{
    if (!table || !inputfileName || !outputFileName)
    {
        fprintf(stderr, "Error: invalid input! --ft_executeBucketFilter()--\n");
        return;
    }

    printf("\nNow please enter one or more bucket indices you want to filter, max. bucket range is from index [0] to [%d].\n", TABLE_SIZE - 1);
    printf("\nYour input numbers will be seperated by 'space' '.' ';' ': ',' or tab\n");
    printf("\nBuckets-> ");

    char input[MAX_INDEX_NUMBER_LENGHT];

    if (!ft_readInput(input, sizeof(input)))
    {
        return;
    }

    printf("\n");

    int selectedBuckets[TABLE_SIZE] = {0};
    int bucketCount = ft_parseBucketIndizes(input, selectedBuckets);

    if (bucketCount == 0)
    {
        return;
    }

    FILE *inputFile = fopen(inputfileName, "r");

    if (!inputFile)
    {
        fprintf(stderr, "Error: failed to open input file! --ft_executeBucketFilter()--\n");
        return;
    }

    FILE *outputFile = fopen(outputFileName, "w");

    if (!outputFile)
    {
        fclose(inputFile);
        fprintf(stderr, "Error: failed to open output file! --ft_executeBucketFilter()--\n");
        return;
    }

    ft_processFileWithBuckets(inputFile, outputFile, table, selectedBuckets, bucketCount);

    ft_printBorder();
    printf("\nFilterd text written to file: <<<%s>>>\n", outputFileName);
    ft_printBorder();

    fclose(inputFile);
    fclose(outputFile);
}