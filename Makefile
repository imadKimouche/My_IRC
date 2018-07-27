##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## This Makefile compiles the SRC
##

SRC_DIR	=	$(realpath ./src)

SRC_DIR_SERVER	=	$(SRC_DIR)/server

SRC_DIR_CLIENT	=	$(SRC_DIR)/client

SRC_S	=	$(SRC_DIR_SERVER)/main.c \
		$(SRC_DIR_SERVER)/usage.c \
		$(SRC_DIR_SERVER)/list_creation.c \
		$(SRC_DIR_SERVER)/list_editing.c\
		$(SRC_DIR_SERVER)/tools.c \
		$(SRC_DIR_SERVER)/tools_list.c \
		$(SRC_DIR_SERVER)/s_create.c\
		$(SRC_DIR_SERVER)/server.c \
		$(SRC_DIR_SERVER)/server2.c \
		$(SRC_DIR_SERVER)/server_IO.c \
		$(SRC_DIR_SERVER)/server_cmd.c \
		$(SRC_DIR_SERVER)/s_select.c \
		$(SRC_DIR_SERVER)/client_cmd.c \
		$(SRC_DIR_SERVER)/client_cmd2.c \
		$(SRC_DIR_SERVER)/client_cmd3.c

SRC_C	=	$(SRC_DIR_CLIENT)/main.c \
				$(SRC_DIR_CLIENT)/gui.c \
				$(SRC_DIR_CLIENT)/actions.c \
				$(SRC_DIR_CLIENT)/client_IO.c \
				$(SRC_DIR_CLIENT)/client.c \
				$(SRC_DIR_CLIENT)/local_cmd.c \
				$(SRC_DIR_CLIENT)/gui_w_main.c \
				$(SRC_DIR_CLIENT)/file_handle.c \
				$(SRC_DIR_CLIENT)/tools.c

OBJ_S	=	$(SRC_S:.c=.o)

OBJ_C	=	$(SRC_C:.c=.o)

CFLAGS	=	-g -I ./include -Wall -Wextra -Wall -lpthread $(GTK_CFLAGS)

GTK_CFLAGS      =       $(shell pkg-config --cflags gtk+-2.0)

GTK_LDFLAGS     =       $(shell pkg-config --libs gtk+-2.0)

NAME		=	server

NAME_CLIENT 	= 	client

all:	server client

server:		$(OBJ_S)
		@gcc -o $(NAME) $(OBJ_S) $(CFLAGS) $(LFLAGS)

client:		$(OBJ_C)
		@gcc -o client $(OBJ_C) $(CFLAGS) $(GTK_LDFLAGS)

clean:
	@rm -f $(OBJ_S)
	@rm -f $(OBJ_C)
	@rm -f *.gcda *.gcno
	@rm -f *~
	@rm -f $(SRC_DIR_SERVER)/*~
	@rm -f $(SRC_DIR)/*~
	@rm -f vgcore.*

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(NAME_CLIENT)

re: fclean all
