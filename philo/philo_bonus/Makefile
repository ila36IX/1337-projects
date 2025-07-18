CC = cc
SRC_FILES= $(wildcard *.c)
SRC_OBJ= $(SRC_FILES:%.c=%.o)
CFLAGS= -Wall -Wextra -Werror
NAME=philo

all: $(NAME)

bonus: all

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
