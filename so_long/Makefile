CC=@cc
NAME=so_long
SRC= $(wildcard *.c)
OBJ= $(SRC:%.c=%.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror -g  -ggdb3

all: libft_rule $(NAME)

# Run "make get_lib" to download the library source code if you didn't have the
# library in your machine
get_lib: libft_rule mlx_linux/libmlx.a game_exec

$(NAME): $(OBJ)
	$(CC) $(OBJ)  -lmlx -lXext -lX11 -L$(LIBFT_DIR) -lft -o $(NAME)

game_exec: mlx_linux/libmlx.a $(OBJ) 
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

libft_rule:
	@$(MAKE) -C $(LIBFT_DIR)

mlx_linux/libmlx.a:
	curl https://cdn.intra.42.fr/document/document/30831/minilibx-linux.tgz -o mlx_linux.tgz
	tar xpf mlx_linux.tgz
	mv minilibx-linux mlx_linux
	rm mlx_linux.tgz
	make -C mlx_linux

run: $(NAME)
	./$(NAME)

clean: 
	rm -f $(OBJ)
	# $(MAKE) -C $(LIBFT_DIR) clean

fclean: 
	rm -f $(OBJ) $(NAME)
	# $(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: re clean fclean run libft_rule get_lib
