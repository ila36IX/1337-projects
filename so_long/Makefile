NAME=so_long
SRC= $(wildcard *.c)
OBJ= $(SRC:%.c=%.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror

# $(NAME): mlx_linux/libmlx.a $(OBJ) 
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g  -ggdb3 -o $(NAME)
#
$(NAME): libft_rule $(OBJ) 
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g  -ggdb3 -L$(LIBFT_DIR) -lft -o $(NAME)

libft_rule:
	@$(MAKE) -C $(LIBFT_DIR)

mlx_linux/libmlx.a:
	curl https://cdn.intra.42.fr/document/document/30831/minilibx-linux.tgz -o mlx_linux.tgz
	tar xpf mlx_linux.tgz
	mv minilibx-linux mlx_linux
	rm mlx_linux.tgz
	make -C mlx_linux

# %.o: %.c
# 	$(CC)  -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c  $< -o $@

run: $(NAME)
	./$(NAME)

clean: 
	rm -f $(OBJ)

fclean: 
	rm -f $(OBJ) $(NAME)

re: fclean run

.PHONY: re clean fclean run
