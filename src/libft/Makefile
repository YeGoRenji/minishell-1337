# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/23 02:54:46 by ylyoussf          #+#    #+#              #
#    Updated: 2023/07/14 01:23:23 by ylyoussf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

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
	  ft_putnbr_fd.c

OBJ = $(SRC:.c=.o)

bonus_src = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstmap_bonus.c

bonus_obj = $(bonus_src:.c=.o)

all : $(NAME) bonus

$(NAME) : $(OBJ)
	ar rcs $@ $^

bonus : $(bonus_obj)
	ar rcs $(NAME) $^

%.o : %.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ) $(bonus_obj)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean re all bonus
