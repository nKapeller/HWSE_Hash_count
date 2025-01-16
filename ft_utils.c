#include "ft_utils.h"
#include "ft_hashTable.h"
#include "ft_structs.h"
#include "ft_print.h"
#include "ft_filterUtils.h"


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void ft_safeStrncpy(char *dest, const char *src, size_t destSize)
{
    strncpy(dest, src, destSize - 1); // Copy with space for null terminator
    dest[destSize - 1] = '\0';        // Explicitly ensure null-termination
}

char *ft_strdupCalloc(const char *source)
{
    size_t length = strlen(source) + 1;

    char *duplicate = calloc(length, sizeof(char));

    if (!duplicate)
    {
        fprintf(stderr, "Allocation failed: strdup");
        return NULL;
    }

    strcpy(duplicate, source);

    return duplicate;
}

int ft_getHashValue(const char *str)
{
    int sum = 0;

    while (*str)
    {
        sum += *str;
        str++;
    }
    return sum % TABLE_SIZE;
}

void ft_flushInputBuffer()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int ft_readInput(char *input, size_t size)
{
    if (!fgets(input, size, stdin))
    {
        fprintf(stderr, "Error, failed to read input\n");
        return 0;
    }
    return 1;
}

void ft_processToken(HashTable_t *table, char *token)
{
    long long index = strtoll(token, NULL, 10); // input string of numbers will be transformed to an long long

    if (index >= 0 && index < TABLE_SIZE)
    {
        ft_printBucket(table->bucket[(int)index], (int)index);
    }
    else
    {
        fprintf(stderr, "Invalid bucket index, skipping.\n");
    }
}

void ft_processBucketIndices(HashTable_t *table, const char *input)
{
    if (!table || !input)
    {
        fprintf(stderr, "Error: invalid input or table.\n");
        return;
    }

    char inputCpy[MAX_INDEX_NUMBER_LENGHT];

    ft_safeStrncpy(inputCpy, input, sizeof(inputCpy));

    char *delimiter = " .;:,\t";
    char *token = strtok(inputCpy, delimiter);

    while (token)
    {
        ft_processToken(table, token);
        token = strtok(NULL, delimiter);
    }
}

    /*
int ft_getSelectedBucket(int selectedBuckets[], size_t bucketSize)
{
    printf("Please select Bucket indizes you want to filter your text with:\n\n--->");



    if(!ft_readInput(input,sizeof(input)))
    {
        fprintf(stderr, "Error: failed to read input! ---ft_getSelectedBucket()---\n");
        return 0;
    }
    char input[MAX_INDEX_NUMBER_LENGHT];
    int selectedCount = ft_parseBucketIndizes(input, selectedBuckets);
    
    if(selectedCount == 0)
    {
        fprintf(stderr, "Invalid bucket selection! ---ft_getSelectedBucket()---\n");
    }
    return selectedCount;
}
    */
