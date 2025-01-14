#include "ft_utils.h"
#include "ft_hashTable.h"
#include "ft_structs.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *ft_strdupCalloc(const char *source)
{
    size_t length = strlen(source) + 1;

    char *duplicate = calloc(length, sizeof(char));

    if (!duplicate)
    {
        fprintf(stderr, "Allocation failed: strdup");
        return NULL;
    }

    strcpy(duplicate, source);

    return duplicate;
}

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
