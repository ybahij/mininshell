NAME = minishell
CC = cc
CFLAGS =  -Wall -Wextra #-Werror -Werror=unused-but-set-variable #-g3 -fsanitize=address

SRC = $(wildcard *.c) $(wildcard */*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
