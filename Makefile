NAME_CLIENT = client
NAME_SERVER = server

SRC_CLIENT = client.c
SRC_SERVER = server.c
SRC_HELPER = helper.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_HELPER = $(SRC_HELPER:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(OBJ_HELPER)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(OBJ_HELPER) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(OBJ_HELPER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_HELPER) -o $(NAME_SERVER)

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_HELPER)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re
