CC = cc
# CFLAGS = -Wall -Wextra -Werror

SRC_FILES= ft_atol.c ksort.c main.c operation_push.c operation_rev_rotate.c operation_rotate.c operation_swap.c parse.c push_swap_helper.c read_ops_bonus.c small_sort.c
SRC_OBJ= $(SRC_FILES:%.c=%.o)

SRC_BONUS = ft_atol.c ksort.c main_bonus.c operation_push.c operation_rev_rotate.c operation_rotate.c operation_swap.c parse.c push_swap_helper.c read_ops_bonus.c small_sort.c
OBJ_BONUS = $(SRC_BONUS:%.c=%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS= -Wall -Wextra -Werror
NAME=push_swap
CHECKER=checker

all: libft_rule $(NAME)

bonus: libft_rule $(CHECKER)

libft_rule:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRC_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

$(CHECKER): $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(LIBFT_DIR) -lft -o $(CHECKER)

clean: 
	@$(RM) $(SRC_OBJ) $(OBJ_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(CHECKER)
	@$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all libft_rule clean fclean re
