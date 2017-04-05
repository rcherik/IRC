# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/20 15:43:04 by rcherik           #+#    #+#              #
#    Updated: 2015/02/20 14:48:12 by rcherik          ###   ########.fr        #
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

NAME = libft.a
CFLAGS = gcc -Wall -Wextra -Werror
IFLAGS = -I include
PATH_SRC = src
PATH_OBJ = obj
FIRST_SRC = $(addprefix $(PATH_SRC)/, $(shell ls -1 $(PATH_SRC) | head -n 1))

SRC = ft_atoi.c\
	  ft_tabfree.c\
	  ft_tablen.c\
	  ft_bzero.c\
	  ft_strlcat.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isprint.c\
	  ft_isdigit.c\
	  ft_itoa.c\
	  ft_lstadd.c\
	  ft_lstnew.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memdel.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_putchar.c\
	  ft_putstr_fd.c\
	  ft_strequ.c\
	  ft_strlen.c\
	  ft_putchar_fd.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strdup.c\
	  ft_strncat.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strsplit.c\
	  ft_strstr.c\
	  ft_strsub.c\
	  ft_strcat.c\
	  ft_strjoin.c\
	  ft_strtrim.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_lstmap.c\
	  ft_lstiter.c\
	  ft_tolower.c\
	  ft_lstdelone.c\
	  ft_lstdel.c\
	  ft_toupper.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))
INCLUDES = include/libft.h\

all: $(NAME)

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c) $(INCLUDES)
	@mkdir -p $(PATH_OBJ)
	@$(CFLAGS) $(IFLAGS) -o $@ -c $<
	@ if [ $< == $(FIRST_SRC) ]; then \
			$(ECHO) "\033[32;01mLibft : [ \033[00m\c"; \
		fi
	@$(ECHO) "\033[32;01m.\033[00m\c"

$(NAME): $(OBJ)
	@$(ECHO) "\033[32;01m ]\033[00m"
	@$(ECHO) "\033[32m[ Objects done ]\033[00m"
	@ar rcs $@ $^
	@$(ECHO) "\033[32m[ Library done ]\033[00m"

clean:
	@rm -f $(OBJ)
	@rm -rf $(PATH_OBJ)
	@$(ECHO) "\033[31m[ Objects deleted ]\033[00m"

fclean: clean
	@rm -rf $(NAME)
	@$(ECHO) "\033[31m[ $(NAME) deleted ]\033[00m"

re: fclean all

.PHONY: all clean fclean re
