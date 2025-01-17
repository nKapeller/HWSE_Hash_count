#ifndef FT_FILTERUTILS_H
#define FT_FILTERUTILS_H

#include "ft_structs.h"

#include <stdio.h>

int ft_parseBucketIndizes(char *inputStr, int *selectedBucketsArray);
int ft_isBucketSelected(int hashValue, const int *selectedBucket, int count);
int ft_isWordInBucket(HashTable_t *table, int bucketIndex, const char *word);
void ft_filterWordsByBucket(HashTable_t *table, FILE *outputFile, const char *line, int bucketCount, const int *selectedBuckets);
void ft_processFileWithBuckets(FILE *inputFile, FILE *outputfile, HashTable_t *table, const int *selectedBuckets, int bucketCount);
void ft_executeBucketFilter(HashTable_t *table, const char *inputfileName, const char *outputFileName);

#endif 