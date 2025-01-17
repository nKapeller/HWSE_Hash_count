#include "ft_print.h"
#include "ft_filterUtils.h"
#include "ft_structs.h"

#include <unistd.h>

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
        fprintf(stderr, "Error: Table is empty! --printTable()--\n");
        return;
    }

    int i = 0;

    while (i < TABLE_SIZE)
    {
        ft_printBucket(table->bucket[i], i);
        i++;
    }

    ft_printBorder();
}

/**
 * @brief
 *
 * @param table
 */

void ft_printSelectedBucket(HashTable_t *table)
{
    if (!table)
    {
        fprintf(stderr, "Error: Table is empty! --ft_printSelectedBucket()--\n");
        return;
    }

    printf("\nDo you want to print out one specific bucket? press 'y' as first letter, if not press any other letter\n");
    printf("\n->");

    char userChoice = getchar();
    ft_flushInputBuffer();

    if (userChoice != 'y' && userChoice != 'Y')
    {
        printf("\nYou choose not to print a specific bucket\n");
        ft_printBorder();
        return;
    }

    printf("\nGreat! Which bucket should it be today may i ask?\n");
    printf("\n->");

    char input[MAX_INDEX_NUMBER_LENGHT];

    if (!fgets(input, sizeof(input), stdin))
    {
        fprintf(stderr, "Error: Faild to read input! --ft_printSelectedBucket()--\n");
        return;
    }
    ft_printBorder();
    ft_processBucketIndices(table, input);
    ft_printBorder();
}

void ft_printHashToBinary(HashTable_t *table, const char *filename)
{
    if (!table || !filename)
    {
        fprintf(stderr, "Error: Invalid input! --ft_printHashToBinary()--\n");
        return;
    }

    FILE *file = fopen(filename, "wb");

    if (!file)
    {
        fprintf(stderr, "Error: Failed to open file! --ft_printHashToBinary()--\n");
        return;
    }

    const int tableSize = TABLE_SIZE;

    fwrite(&tableSize, sizeof(int), 1, file);

    int i = 0;

    while (i < TABLE_SIZE)
    {
        Node_t *current = table->bucket[i];
        Node_t *temp = current;
        
        int count = 0;

        while (temp)
        {
            count++;
            temp = temp->next;
        }

        fwrite(&count, sizeof(int), 1, file);

        while (current)
        {
            fwrite(current->keyString, sizeof(current->keyString), 1, file);
            fwrite(&current->count, sizeof(current->count), 1, file);

            current = current->next;
        }
        i++;
    }
    printf("\nHash was stored in file: <<<%s>>>\n", filename);
    ft_printBorder();

    fclose(file);
}