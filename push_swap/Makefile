CC = @cc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES= $(wildcard *.c)
INC_FILES= $(wildcard *.h)

SRC_OBJ= $(SRC_FILES:%.c=%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: libft_rule run

libft_rule:
	@$(MAKE) -C $(LIBFT_DIR) bonus

run: $(SRC_OBJ) $(INC_FILES) $(LIBFT)
	$(CC)  $(CFLAGS) $(SRC_OBJ) -Llibft -lft -o run

start: run
	@./run

clean: 
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	@$(RM) $(SRC_OBJ)
	@$(RM) run
	@$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all run clean fclean re
