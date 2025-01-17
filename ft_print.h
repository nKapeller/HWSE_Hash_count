#ifndef FT_PRINT_H
#define FT_PRINT_H

#define MAX_WORDS_PER_LINE 10

#include "ft_utils.h"
#include "ft_hashTable.h"
#include "ft_structs.h"

void ft_printBucket(Node_t *bucket, int index);
void ft_printTable(HashTable_t *table);
void ft_printSelectedBucket(HashTable_t *table);
void ft_printHashToBinary(HashTable_t *table, const char *filename);

#endif