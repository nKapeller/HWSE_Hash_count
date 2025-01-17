#define _POSIX_C_SOURCE 200809L

#include "ft_print.h"
#include "ft_filterUtils.h"
#include "ft_structs.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief
 *  Helper function to print all (keys) strings stored in a bucket
 *
 * @param bucket    Pointer to a struct/list Node_t which should be processed
 * @param index     Index of the bucket
 */
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

/**
 * @brief 
 * Function to print the whole Hashtable, bucket by bucket 
 *
 * @param table     Pointer to a Hashtable struct/list which should pe processed
 */
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
 * Function to get user input to select which bucket should be printed
 * then the input will be checkd if valid or not,
 * if valid it will print the selcted bucket with the help of other functions
 *
 * @param table     Pointer to a Hashtable struct/list 
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

    printf("\nGreat choice! Which bucket should it be today may i ask? choose an index between [0] and [%d]\n", TABLE_SIZE - 1);
    printf("\n->");

    char *input = NULL;
    size_t len = 0;

    if (getline(&input, &len, stdin) == -1)
    {
        fprintf(stderr, "Error: Failed to read input! --ft_printSelectedBucket()--\n");
        free(input);
        return;
    }

    input[strcspn(input, "\n")] = '\0';
    ft_printBorder();
    ft_processBucketIndices(table, input);
    ft_printBorder();
}

/**
 * @brief 
 * Function that opens a binary file and prints hashvalues as binary in it
 * 
 * @param table        Pointer to a Hashtable struct/list 
 * @param filename     Filename of the output binare file
 */

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