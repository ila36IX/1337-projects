CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER_SRC= server.c
CLIENT_SRC= client.c

SERVER_OBJ= $(SERVER_SRC:%.c=%.o)
CLIENT_OBJ= $(CLIENT_SRC:%.c=%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: libft_rule server client

libft_rule:
	$(MAKE) -C $(LIBFT_DIR)

server: $(SERVER_OBJ) $(LIBFT)
	$(CC)  $(CFLAGS) $(SERVER_OBJ) -Llibft -lft -o server

client: $(CLIENT_OBJ) $(LIBFT)
	$(CC)  $(CFLAGS) $(CLIENT_OBJ) -Llibft -lft -o client

clean: 
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)
	$(RM) client server
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(SERVER_OBJ) $(CLIENT_OBJ)
