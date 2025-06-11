NAME = philo

SRC = philo.c parser.c free_all.c utils.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

CC = cc

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS)  -pthread $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all 

.PHONY: all bonus clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
MAGENTA = \033[1;35m
CYAN = \033[1;36m