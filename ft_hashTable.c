#include "ft_hashTable.h"
#include "ft_structs.h"
#include "ft_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node_t *ft_createNode(const char *str)
{
    if (!str)
    {
        fprintf(stderr, "Error string is empty\n");
        return NULL;
    }

    Node_t *newNode = calloc(1, sizeof(Node_t));

    if (!newNode)
    {
        fprintf(stderr, "Allocation for node failed\n"); // check later in main again?
        return NULL;
    }

    newNode->keyString = ft_strdupCalloc(str);
    newNode->count = 1;

    return newNode;
}

HashTable_t *ft_createHashTable()
{
    HashTable_t *table = calloc(1, sizeof(HashTable_t));

    if (!table)
    {
        fprintf(stderr, "Allocation for hash table failed\n"); // check later in main again?
        return NULL;
    }
    return table;
}

void ft_insertNewNode(HashTable_t *table, const char *str)
{
    if (!str)
    {
        fprintf(stderr, "Error string is empty\n");
        return;
    }

    int hashValue = ft_getHashValue(str);
    Node_t *currentNode = table->bucket[hashValue];

    if (!currentNode || strcmp(str, currentNode->keyString) < 0) // check if list is empty or current node comes for head
    {
        Node_t *newNode = ft_createNode(str);

        if (!newNode)
        {
            fprintf(stderr, "Error failed to create node");
            return;
        }

        newNode->next = table->bucket[hashValue]; // newNode points to old head or NULL if list is empty
        table->bucket[hashValue] = newNode;       // newNode becomes new head of list

        return;
    }

    while (currentNode->next)
    {
        int cmp = strcmp(currentNode->next->keyString, str);

        if (cmp == 0) // same string increment word count in bucket
        {
            currentNode->next->count++;
            return;
        }

        if (cmp > 0)
        {
            Node_t *newNode = ft_createNode(str);

            if (!newNode)
            {
                fprintf(stderr, "Error failed to create node");
                return;
            }

            newNode->next = currentNode->next;
            currentNode->next = newNode;

            return;
        }
        currentNode = currentNode->next;

        Node_t *newNode = ft_createNode(str);

        if (!newNode)
        {
            fprintf(stderr, "Error failed to create node");
            return;
        }
        currentNode->next = newNode;
    }
}
