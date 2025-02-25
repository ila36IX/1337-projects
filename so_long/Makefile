NAME=so_long
SRC= $(wildcard *.c)
OBJ= $(SRC:%.c=%.o)

$(NAME): mlx_linux/libmlx.a $(OBJ) 
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g -o $(NAME)

mlx_linux/libmlx.a:
	curl https://cdn.intra.42.fr/document/document/30831/minilibx-linux.tgz -o mlx_linux.tgz
	tar xpf mlx_linux.tgz
	mv minilibx-linux mlx_linux
	rm mlx_linux.tgz
	make -C mlx_linux

%.o: %.c
	$(CC)  -I/usr/include -Imlx_linux -O3 -c $< -o $@

run: $(NAME)
	./$(NAME)

clean: 
	rm -f $(OBJ) $(NAME)

re: clean $(NAME) run

.PHONY: re
