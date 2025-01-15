#include "ft_print.h"
#include "termios.h"
#include "unistd.h"

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
        printf("%s(%d)", bucket->keyString, bucket->count);
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

void ft_printSelectedBucket(HashTable_t *table)
{
    if (!table)
    {
        fprintf(stderr, "Error, table is empty (ft_printSelectedBucket())\n");
        return;
    }

    printf("\nDo you want to print out one specific bucket? press 'y' as first letter, if not press any other button\n");

    char userChoice = getchar();
    ft_flushInputBuffer();

    if (userChoice != 'y' && userChoice != 'Y')
    {
        printf("You choose not to print a specific bucket\n");
        return;
    }

    printf("Great! Which bucket should it be today may i ask?\n");

    char input[100];

    if (!fgets(input, sizeof(input), stdin))
    {
        fprintf(stderr, "Error, faild to read input\n");
        return;
    }

    ft_processBucketIndices(table, input);
}
