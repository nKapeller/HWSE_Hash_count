TARGET = execute
CC = @gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter
RM = rm -f

SRC =  ft_utils.c ft_print.c ft_hashTable.c ft_filterUtils.c ft_fileHandler.c Main.c
OBJ = $(SRC:.c=.o)

DEPS = ft_utils.h ft_print.h ft_hashTable.h ft_filterUtils.h ft_fileHandler.h ft_structs.h

all: $(TARGET)
	
$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

clean: 
	@$(RM) $(OBJ) 

fclean: clean
	@$(RM) $(TARGET) 

run: $(TARGET)
	./$(TARGET) -f demo.txt

PHONY: clean fclean all run 

