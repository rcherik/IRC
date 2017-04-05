# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/18 14:42:57 by rcherik           #+#    #+#              #
#    Updated: 2015/06/23 16:57:10 by rcherik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)
ifeq ($(OS),Linux)
SHELL := /bin/bash
else
SHELL := /bin/sh
endif

ifeq ($(OS),Linux)
ECHO = echo -e
else
ECHO = echo
endif

NAME = ft_irc
SERVER = serveur
CLIENT = client
CFLAGS = gcc -Wall -Wextra -Werror
OFLAGS = -I libft/include/. -I ./includes/.
LFLAGS = -Llibft -lft
LIB = libft/libft.a
MKLIB = make -C libft
PATH_SRC_SERVER = $(SERVER)_src
PATH_SRC_CLIENT = $(CLIENT)_src
PATH_OBJ_SERVER = obj_$(SERVER)
PATH_OBJ_CLIENT = obj_$(CLIENT)
SERVER_SRC = main.c\
			 do_read.c\
			 do_write.c\
			 server_loop.c\
			 ft_error.c\
			 start_server.c\
			 send_to_clients.c\
			 commands.c\
			 commands_util.c\
			 channels.c\

CLIENT_SRC = main.c\
			 ft_error.c\
			 client_check_fd.c\
			 start_client.c\

OBJ_SERVER = $(patsubst %.c, $(PATH_OBJ_SERVER)/%.o, $(SERVER_SRC))
OBJ_CLIENT = $(patsubst %.c, $(PATH_OBJ_CLIENT)/%.o, $(CLIENT_SRC))

INCLUDES = 	includes/client.h\
			includes/server.h

all : $(NAME)

$(NAME) : $(SERVER) $(CLIENT) $(INTERFACE)

$(PATH_OBJ_SERVER)/%.o : $(addprefix $(PATH_SRC_SERVER)/, %.c) $(INCLUDES)
	@mkdir -p $(PATH_OBJ_SERVER)
	@$(CFLAGS) $(OFLAGS) -o $@ -c $<

$(PATH_OBJ_CLIENT)/%.o : $(addprefix $(PATH_SRC_CLIENT)/, %.c) $(INCLUDES)
	@mkdir -p $(PATH_OBJ_CLIENT)
	@$(CFLAGS) $(OFLAGS) -o $@ -c $<

$(LIB) :
	@$(MKLIB)

$(SERVER) : $(LIB) $(OBJ_SERVER) $(INCLUDES)
	@$(ECHO) "\033[32m[ $(SERVER) objects done ]\033[00m"
	@$(CFLAGS) -o $(SERVER) $(OBJ_SERVER) $(LFLAGS)
	@$(ECHO) "\033[32m[ $(SERVER) compiled ]\033[00m"

$(CLIENT) : $(LIB) $(OBJ_CLIENT) $(INCLUDES)
	@$(ECHO) "\033[32m[ $(CLIENT) objects done ]\033[00m"
	@$(CFLAGS) -o $(CLIENT) $(OBJ_CLIENT) $(LFLAGS)
	@$(ECHO) "\033[32m[ $(CLIENT) compiled ]\033[00m"

lib :
	@$(MKLIB)
	@make
	@$(ECHO) "\033[32m[ Library compiled ]\033[00m"

clean :
	@$(MKLIB) clean
	@rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	@rm -rf $(PATH_OBJ_SERVER) $(PATH_OBJ_CLIENT)
	@$(ECHO) "\033[31m[ ./$(SERVER) ./$(CLIENT) : objects deleted ]\033[00m"

fclean : clean
	@$(MKLIB) fclean
	@rm -f $(SERVER) $(CLIENT)
	@$(ECHO) "\033[31m[ ./$(SERVER) ./$(CLIENT) deleted ]\033[00m"

re : fclean all

.PHONY : fclean re clean all lib
