# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 00:52:37 by ylyoussf          #+#    #+#              #
#    Updated: 2023/07/20 00:41:59 by ylyoussf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g  

OBJSFOLDER = objs/

SRCS_LEXER = lexer.c \
			 lexer_utils.c

SRCS_PARSER = parser.c

SRCS_AST = ast.c

OBJS_FILES = $(SRCS_LEXER:.c=.o) \
			 $(SRCS_PARSER:.c=.o) \
			 $(SRCS_AST:.c=.o) \
			 main.o

LIBFT = src/libft/libft.a

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = Makefile

all: $(OBJSFOLDER) $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C src/libft

$(OBJSFOLDER):
	@mkdir objs

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -Lsrc/libft -lft -lreadline

$(OBJSFOLDER)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/lexer/%.c include/lexer.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/parser/%.c include/parser.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/parser/ast/%.c include/ast.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)
	make fclean -C src/libft

clean:
	rm -rf $(OBJS)
	make clean -C src/libft

.PHONY: all clean fclean re
