CC = @cc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES= $(wildcard *.c)
SRC_OBJ= $(SRC_FILES:%.c=%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
NAME=push_swap

all: libft_rule $(NAME)

libft_rule:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRC_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

clean: 
	@$(RM) $(SRC_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all libft_rule clean fclean re
