#ifndef FT_PRINT_H
#define FT_PRINT_H

#define MAX_WORDS_PER_LINE 10

#include "ft_utils.h"
#include "ft_hashTable.h"
#include "ft_structs.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void ft_printBucket(Node_t *bucket, int index);
void ft_printTable(HashTable_t *table);
void ft_printSelectedBucket(HashTable_t *table);

#endif