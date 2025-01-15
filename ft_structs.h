#ifndef FT_STRUCTS_H
#define FT_STRUCTS_H

#define TABLE_SIZE 31

typedef struct Node_t
{
    char *keyString;
    int count;
    struct Node_t *next;

} Node_t;

typedef struct HashTable_t
{
    Node_t *bucket[TABLE_SIZE];

} HashTable_t;

#endif