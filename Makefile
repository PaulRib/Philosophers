NAME = philo

SRC = free_all.c loop.c monitoring.c parser.c philo.c thread.c time.c utils.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

CC = cc

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo -n "$(BLUE)Compiling: ["
	@i=0; total=30; \
	while [ $$i -le $$total ]; do \
		percent=$$(( 100 * $$i / $$total )); \
		done=$$(( $$total - $$i )); \
		printf "\r$(BLUE)Compiling: ["; \
		printf "%0.s█" `seq 1 $$i`; \
		printf "%0.s " `seq 1 $$done`; \
		printf "] %3d%%" $$percent; \
		sleep 0.02; \
		i=`expr $$i + 1`; \
	done; \
	echo "$(RESET)"
	@echo ""
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(CYAN)    ⚙️  Philosopher compilation complete! ⚙️    $(RESET)"
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)\n"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)


clean:
	@rm -rf $(OBJS) > /dev/null
	@echo "\n$(YELLOW)Cleaning up... 🧹\n"

fclean: clean
	@rm -rf $(NAME) > /dev/null
	@echo "\n$(RED)Deleting EVERYTHING! 🗑️\n"

re : fclean all 

.PHONY: all bonus clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE	= \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m