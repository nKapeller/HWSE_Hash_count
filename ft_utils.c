#include "ft_utils.h"
#include "ft_structs.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

int ft_getHashValue(char *str)
{
    int sum = 0;

    while (*str)
    {
        sum += *str;
        str++;
    }
    return sum % TABLE_SIZE;
}

void ft_printBucket(Node_t *bucket, int index)
{
    if (!bucket)
    {
        printf("Bucket [%d] is empty\n", index);
        return;
    }

    int count = 0;

    printf("Bucket [%d]:\n", index);

    while (bucket)
    {
        printf("%s (%d)", bucket->keyString, bucket->count);
        bucket = bucket->next;
        count++;

        if (!bucket || count % MAX_WORDS_PER_LINE == 0)
        {
            printf("\n");
        }

        printf(", ");
    }
}

void ft_printTable(HashTable_t *table)
{
    if(!table)
    {
        fprintf(stderr, "Error Table is Empty\n");
        return;
    }
    
    int i = 0;

    while(i < TABLE_SIZE)
    {
        ft_printBucket(i, table->bucket);
    }
}