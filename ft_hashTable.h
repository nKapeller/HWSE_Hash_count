#ifndef FT_HASHTABLE_H
#define FT_HASHTABLE_H

Node_t *ft_createNode(const char *str);
HashTable_t *ft_createHashTable();
void ft_insertNewNode(HashTable_t *table, const char *str);

#endif