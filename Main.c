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