#include "ft_utils.h"
#include "ft_hashTable.h"
#include "ft_structs.h"
#include "ft_print.h"
#include "ft_filterUtils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**
 * @brief
 * Function to print a line of '=' to make the terminal output more structured
 */
void ft_printBorder()
{
    printf("\n======================================================================================================\n");
}

/**
 * @brief
 *  Function works like included strcpy()
 *  but always sets a null terminator at the end of the string
 *
 * @param dest          String which ist destination of copying
 * @param src           String which is the source for copying
 * @param destSize      Size of the destination String
 */
void ft_safeStrncpy(char *dest, const char *src, size_t destSize)
{
    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
}

/**
 * @brief
 * Same function as included strdup()
 * but only with calloc() instead of malloc for extra extra safety
 *
 * @param source    String which should be duplicated
 * @return char*    Duplicated string
 */
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

/**
 * @brief 
 * Function to calculate the hashvalue of a string
 * takes the sum of every char and then uses modulo the amount of buckets in a Hashtable 
 * 
 * @param str       String to calculate hashvalue from
 * @return int      Hashvalue 
 */
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

/**
 * @brief 
 * Function to clear the input buffer so no more characters are in it 
 * and is ready for the next user input
 */

void ft_flushInputBuffer()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * @brief 
 * Function to read user input and check if it is valid, 
 * processes it (checks for numeric and delimiters only) and returns "1" if it was succesful 
 * 
 * @param inputStr   String where user input get stored
 * @param size       Number of chars that can safely be stored in inputString
 * @return int       Returns 1 if succesfull and 0 if not 
 */
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

/**
 * @brief 
 * Helperfunction to transform the string to a long long int 
 * and then checks if the provided number is in range of the bucket indices
 * 
 * @param table     Pointer to Hashtable struct/list
 * @param token     String to transform and check
 */

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

/**
 * @brief 
 * Function to process input string, makes tokens with the help of delimiters
 * then sends it to ft_processToken for further processing
 * 
 * @param table     Pointer to Hashtable struct/list
 * @param input     Input string of bucket indizes
 */

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