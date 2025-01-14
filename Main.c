#include "ft_utils.h"
#include "ft_fileHandler.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    const char *filename = ft_getFileName(argc, argv);

    if(!filename)
    {
        fprintf(stderr, "Filename initialisation went wrong");
        return 1;
    }
    printf("\n %s\n", filename);

    FILE *file = ft_openFile(filename);

    if(!file)
    {
        fprintf(stderr, "Could not open file");
        return 1;
    }

    HashTable_t *table = ft_createHashTable();
    if(!table)
    {
        fprintf(stderr, "Error Main -27");
        return 1;
    }

    ft_readAndProcessFile(file, table);

       fclose(file);

    // Print the hash table
    ft_printTable(table);

    // Free the hash table memory
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node_t *current = table->bucket[i];
        while (current)
        {
            Node_t *temp = current;
            current = current->next;
            free(temp->keyString);
            free(temp);
        }
    }
    free(table);
    
    /*
    FILE *file = NULL;

    unsigned int bufferSize = 256;

    char *line = calloc(bufferSize, sizeof(char));

    if (!line)
    {
        fprintf(stderr, "Error allocating");
        fclose(file);
        return 1;
    }

    while (fgets(line, bufferSize, file) != '\n')
    {
        printf("%s********************", line);
    }

    if (ferror(file))
    {
        fprintf(stderr,"Error reading");
        fclose(file);
        return 1;
    }

    free(line);
    fclose(file);
*/
    return 0;
        
}