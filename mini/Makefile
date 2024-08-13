NAME = minishell
CC = cc
CFALGS =  -Wall -Wextra -Werror -fsanitize=address,undefined,leak -g3 -o0
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFALGS) -o $(NAME) $(OBJ) -lreadline

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


