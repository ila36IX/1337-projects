CC = @cc
CFLAGS = -Wall -Wextra -Werror

SERVER_SRC= server.c
CLIENT_SRC= client.c

SERVER_OBJ= $(SERVER_SRC:%.c=%.o)
CLIENT_OBJ= $(CLIENT_SRC:%.c=%.o)

LIBFT_DIR= "libft"
LIBFT= "libft.a"


all: server client

clinet: $(CLIENT_SRC) $(LIBFT)
	cc $(CLIENT_SRC) -L$(LIBFT_DIR) -lft -o client

server: $(SERVER_SRC) $(LIBFT)
	cc $(SERVER_SRC) -L$(LIBFT_DIR) -lft -o server

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
