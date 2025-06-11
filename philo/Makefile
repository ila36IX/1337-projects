CC = cc
SRC_FILES= atoi.c  main.c  monitoring.c  thread.c  timer_helpers.c
SRC_OBJ= $(SRC_FILES:%.c=%.o)
CFLAGS= -Wall -Wextra -Werror -g -ggdb3
NAME=philo

all: $(NAME)

bonus: libft_rule $(CHECKER)

$(NAME): $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $(NAME)

run: all
	./$(NAME)
clean: 
	@$(RM) $(SRC_OBJ)

fclean: clean
	@$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(SRC_OBJ)
