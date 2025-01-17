#include "ft_utils.h"
#include "ft_hashTable.h"
#include "ft_structs.h"
#include "ft_print.h"
#include "ft_filterUtils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void ft_printBorder()
{
    printf("\n======================================================================================================\n");
}

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
        fprintf(stderr, "Error: Allocation failed! --ft_strdupCalloc()--\n");
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

int ft_readInput(char *inputStr, size_t size)
{
    if (!fgets(inputStr, size, stdin))
    {
        fprintf(stderr, "Error: Failed to read input --ft_readInput()--\n");
        return 0;
    }

    inputStr[strcspn(inputStr, "\n")] = '\0';

    size_t i = 0;
    int flag = 1;

    while (i < strlen(inputStr))
    {
        if (!isdigit(inputStr[i]) && !strchr(" .;:,\t", inputStr[i]))
        {
            flag = 0;
            break;
        }
        i++;
    }

    if (flag)
    {
        return 1;
    }
    else
    {
        ft_printBorder();
        fprintf(stderr, "\nError: Dedected an invalid input character! --ft_readInput()--\n");
        ft_printBorder();
    }
    return 0;
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
        fprintf(stderr, "Error: Invalid input or table! --ft_processBucketIndices()--\n");
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