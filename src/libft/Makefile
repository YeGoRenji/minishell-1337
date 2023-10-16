# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/23 02:54:46 by ylyoussf          #+#    #+#              #
#    Updated: 2023/10/16 03:11:37 by afatimi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -I ../../include -g -fsanitize=address

SRC = ft_isalpha.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_strlen.c \
	  ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_memchr.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strdup.c \
	  ft_memcmp.c \
	  ft_strncmp.c \
	  ft_strcmp.c \
	  ft_calloc.c \
	  ft_strnstr.c \
	  ft_strlcpy.c \
	  ft_strlcat.c \
	  ft_atoi.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_striteri.c \
	  ft_strmapi.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_malloc.c \
	  get_next_line.c \
	  get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $@ $^

%.o : %.c libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re all
