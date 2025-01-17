#ifndef FT_UTILS_H
#define FT_UTILS_H

#include "ft_utils.h"
#include "ft_hashTable.h"
#include "ft_structs.h"

#include <stdio.h>

char *ft_strdupCalloc(const char *source);
char *ft_strdupCalloc(const char *source);
int ft_getHashValue(const char *str);
int ft_readInput(char *input, size_t size);
void ft_printBorder();
void ft_flushInputBuffer();
void ft_processToken(HashTable_t *table, char *token);
void ft_processBucketIndices(HashTable_t *table, const char *input);

#endif