NAME=so_long
SRC= $(wildcard *.c)
OBJ= $(SRC:%.c=%.o)

%.o: %.c
	$(CC)  -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

run: $(NAME)
	./$(NAME)

re: $(NAME)
	rm -f $(OBJ) $(NAME)
