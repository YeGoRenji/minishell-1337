CC = cc

NAME = minishell

CFLAGS = -Wall -Wextra -Werror # -g -ggdb3 -fsanitize=address

M_SRC = minishell.c builtin_utils.c builtins.c

M_OBJ = $(M_SRC:.c=.o)

OBJSFOLDER = ../objs/

OBJ = $(foreach obj, $(M_OBJ), $(OBJSFOLDER)$(obj))

LIBFT = libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)/libft.a
	echo lol
#$(NAME):
#	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a -o $(NAME)

$(LIBFT)/libft.a:
	make -C $(LIBFT) all

$(OBJSFOLDER)%.o : %.c # TODO : add minishell.c here
	$(CC) $(CFLAGS) -c $< -o ../objs/$@

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re bonus
