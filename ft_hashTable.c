#include "ft_hashTable.h"
#include "ft_structs.h"
#include "ft_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief 
 * Function to create a node in a linked list 
 * 
 * @param str           String that was hashed and is ready to be stored in the list
 * @return Node_t*      Pointer to a new allocated Node struct
 */

Node_t *ft_createNode(const char *str)
{
    if (!str)
    {
        fprintf(stderr, "Error: string is empty! --ft_createNode()--\n");
        return NULL;
    }

    Node_t *newNode = calloc(1, sizeof(Node_t));

    if (!newNode)
    {
        fprintf(stderr, "Error: Allocation for node failed! --ft_creatNode()--\n");
        return NULL;
    }

    newNode->keyString = ft_strdupCalloc(str);
    newNode->count = 1;

    return newNode;
}

/**
 * @brief 
 * Function to create a new HashTable struct and safely allocate memmory for it 
 * 
 * @return HashTable_t*     Pointer to Hashtable struct
 */

HashTable_t *ft_createHashTable()
{
    HashTable_t *table = calloc(1, sizeof(HashTable_t));

    if (!table)
    {
        fprintf(stderr, "Error: Allocation for hash table failed! --ft_createHashTable()--\n"); 
        return NULL;
    }
    return table;
}

/**
 * @brief
 * Function to place the word with the help of the hascount
 * in his right bucket sorted in alpabetical order
 *
 * @param table     Pointer to hashtable struct
 * @param str       String from the input File
 */

void ft_insertNewNode(HashTable_t *table, const char *str)
{
    if (!str)
    {
        fprintf(stderr, "Error: String is empty! --ft_insertNewNode()--\n");
        return;
    }

    int hashValue = ft_getHashValue(str);
    Node_t *currentNode = table->bucket[hashValue];

    if (!currentNode || strcmp(str, currentNode->keyString) < 0) 
    {
        Node_t *newNode = ft_createNode(str);

        if (!newNode)
        {
            fprintf(stderr, "Error: Failed to create node! --ft_insertNewNode()--\n");
            return;
        }

        newNode->next = table->bucket[hashValue]; 
        table->bucket[hashValue] = newNode;       

        return;
    }

    while (currentNode)
    {
        if (strcmp(currentNode->keyString, str) == 0) 
        {
            currentNode->count++;
            return;
        }

        if (!currentNode->next || strcmp(currentNode->next->keyString, str) > 0)
        {
            Node_t *newNode = ft_createNode(str);

            if (!newNode)
            {
                fprintf(stderr, "Error: Failed to create node! --ft_insertNewNode()--\n");
                return;
            }

            newNode->next = currentNode->next;
            currentNode->next = newNode;

            return;
        }
        currentNode = currentNode->next;
    }
}

/**
 * @brief 
 * Function to free all allocated memmory so it can be used again
 * 
 * @param table     Pointer to Hashtable struct which should be free'd
 */
void ft_freeHashTable(HashTable_t *table)
{
    if (!table)
    {
        fprintf(stderr, "Error: Table is empty! --ft_freeHashTable()--\n");
        return;
    }

    int i = 0;

    while (i < TABLE_SIZE)
    {
        Node_t *currentBucket = table->bucket[i];

        while (currentBucket)
        {
            Node_t *temp = currentBucket;
            currentBucket = currentBucket->next;
            free(temp->keyString);
            free(temp);
        }
        i++;
    }
    free(table);
}