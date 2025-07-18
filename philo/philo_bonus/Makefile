CC        = cc
SRC_FILES = atoi.c main.c philo_process.c routines.c time_helpers.c utiles.c
SRC_OBJ   = $(SRC_FILES:%.c=%.o)
CFLAGS    = -Wall -Wextra -Werror
NAME      = philo_bonus

all: $(NAME)

bonus: all

$(NAME): $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $(NAME)

clean: 
	$(RM) $(SRC_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
.SECONDARY: $(SRC_OBJ)
