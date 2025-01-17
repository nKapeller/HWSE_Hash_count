#ifndef FT_HASHTABLE_H
#define FT_HASHTABLE_H

#include "ft_hashTable.h"
#include "ft_structs.h"
#include "ft_utils.h"

#include <stdio.h>

Node_t *ft_createNode(const char *str);
HashTable_t *ft_createHashTable();
void ft_insertNewNode(HashTable_t *table, const char *str);
void ft_freeHashTable(HashTable_t *table);

#endif