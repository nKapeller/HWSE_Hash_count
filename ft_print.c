#include "ft_print.h"

void ft_printBucket(Node_t *bucket, int index)
{
    if (!bucket)
    {
        printf("Bucket [%d] is empty\n", index);
        return;
    }

    int count = 0;

    printf("Bucket [%d]: ", index);

    while (bucket)
    {
        printf("%s (%d)", bucket->keyString, bucket->count);
        bucket = bucket->next;
        count++;

        if (!bucket || count % MAX_WORDS_PER_LINE == 0)
        {
            printf("\n");
        }
        else
        {
            printf(", ");
        }
    }
}

void ft_printTable(HashTable_t *table)
{
    if (!table)
    {
        fprintf(stderr, "Error, Table is NULL\n");
        return;
    }

    int i = 0;

    while (i < TABLE_SIZE)
    {
        ft_printBucket(table->bucket[i], i);
        i++;
    }
}

void ft_printSelectedBucket(HashTable_t *table, int index)
{
    if (!table)
    {
        fprintf(stderr, "Error, table is NULL (ft_printSelectedBucket())\n");
        return;
    }

    if (index >= 0 && index < TABLE_SIZE)
    {
        ft_printBucket(table->bucket[index], index);
    }
    else
    {
        fprintf(stderr, "Sorry please enter a valid index, between 0 and %d\n", TABLE_SIZE - 1);
    }
}
