#include "ft_utils.h"
#include "ft_hashTable.h"
#include "ft_structs.h"
#include "ft_print.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

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

void ft_processToken(HashTable_t *table, char *token)
{
    long long index = strtoll(token, NULL, 10);

    if (index >= 0 && index < TABLE_SIZE)
    {
        ft_printBucket(table->bucket[(int)index], (int)index);
    }
    else
    {
        fprintf(stderr, "Invalid bucket index %lld, skipping.\n", index);
    }
}

void ft_processBucketIndices(HashTable_t *table, const char *input)
{
    if (!table || !input)
    {
        fprintf(stderr, "Error: invalid input or table.\n");
        return;
    }

    char inputCpy[100];

    ft_safeStrncpy(inputCpy, input, sizeof(inputCpy));

    char *token = strtok(inputCpy, " ,./-_\t");

    while (token)
    {
        ft_processToken(table, token);
        token = strtok(NULL, " ,./-_\t");
    }
}
