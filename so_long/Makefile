CC=cc
NAME=so_long
SRC= $(wildcard *.c)
BONUS_SRC= bonus/alloc_assets_bonus.c bonus/alloc_enemy_bonus.c bonus/alloc_player_bonus.c bonus/character_movements_0_bonus.c bonus/character_movements_1_bonus.c bonus/error_handlers_bonus.c bonus/frames_controller_bonus.c bonus/free_mem_bonus.c bonus/init_game_bonus.c bonus/key_hooks_bonus.c bonus/main_bonus.c bonus/map_path_checker_bonus.c bonus/map_reader_bonus.c bonus/movements_controller_bonus.c bonus/parse_bonus.c bonus/parse_utils_bonus.c bonus/renders_0_bonus.c bonus/renders_1_bonus.c bonus/utils_bonus.c
OBJ= $(SRC:%.c=%.o)
BONUS_OBJ= $(BONUS_SRC:%.c=%.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11
BONUS = .bst

all: libft_rule $(NAME)

bonus: libft_rule $(BONUS)

$(BONUS): $(BONUS_OBJ)
	@touch $(BONUS)
	$(CC) $(BONUS_OBJ)  $(MLXFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Run "make get_lib" to download the library source code if you didn't have the
# library in your machine
get_lib: libft_rule mlx_linux/libmlx.a game_exec

$(NAME): $(OBJ)
	$(CC) $(OBJ)  $(MLXFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

game_exec: mlx_linux/libmlx.a $(BONUS_SRC) 
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
	rm -f $(OBJ) $(BONUS_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: 
	rm -f $(NAME) $(OBJ) $(BONUS_OBJ)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: re clean fclean run libft_rule get_lib
