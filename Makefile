# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 00:52:37 by ylyoussf          #+#    #+#              #
#    Updated: 2023/10/12 20:27:28 by ylyoussf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RL_PATH =$(shell brew --prefix readline)

LIB = -L $(RL_PATH)/lib -lreadline

CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(RL_PATH)/include -fsanitize=address -g

OBJSFOLDER = objs/

SRCS_LEXER = lexer.c \
			 lexer_utils.c \
			 lexer_utils2.c \
			 tok_list.c

SRCS_PARSER = parser.c

SRCS_AST = ast.c \
		   ast_utils.c \
		   ast_utils2.c \
		   rdescent.c

SRCS_ERR = error.c

SRCS_EXE = executor.c \
		   exec_binary.c \
		   exec_unary.c \
		   exec_utils.c \
		   exec_utils2.c

SRCS_EXPAND = expander.c \
			  expander_utils.c \
			  string_list.c \
			  string_list_utils.c \
			  wild_card.c

SRCS_SB = sb.c \
		  sb_utils.c

SRCS_HEREDOC = heredoc.c

SRCS_SIGNALS = signals.c

BUILTINS_FOLD = src/minishell_builtins/

BUILTINS_FILES = builtin_dispatcher.c \
				builtin_utils.c \
				cd/cd.c \
				echo/echo.c \
				echo/utils.c \
				env/env.c \
				env/utils.c \
				exit/exit.c \
				export/export.c \
				export/utils.c \
				export/validation_utils.c \
				global_utils.c \
				lst_operations.c \
				pwd/pwd.c \
				pwd/utils.c \
				unset/unset.c \
				unset/utils.c

SRCS_HACKS		= hacks.c

SRCS_BUILTINS = $(foreach file, $(BUILTINS_FILES), $(BUILTINS_FOLD)$(file))

OBJS_FILES = $(SRCS_LEXER:.c=.o) \
			 $(SRCS_PARSER:.c=.o) \
			 $(SRCS_AST:.c=.o) \
			 $(SRCS_ERR:.c=.o) \
			 $(SRCS_EXE:.c=.o) \
			 $(SRCS_SB:.c=.o) \
			 $(SRCS_EXPAND:.c=.o) \
			 $(SRCS_HEREDOC:.c=.o) \
			 $(SRCS_SIGNALS:.c=.o) \
			 $(SRCS_HACKS:.c=.o) \
			 main.o

LIBFT = src/libft/libft.a

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = include/globals.h

L_BUILTINS = $(BUILTINS_FOLD)/libbuiltins.a

all: $(OBJSFOLDER) $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C src/libft

$(OBJSFOLDER): 
	@mkdir objs

$(L_BUILTINS): $(SRCS_BUILTINS)
	make -C $(BUILTINS_FOLD)

$(NAME): $(OBJS) $(L_BUILTINS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME) -L$(BUILTINS_FOLD) -lbuiltins -Lsrc/libft -lft $(LIB)

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

$(OBJSFOLDER)%.o: src/execution/%.c include/executor.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/expander/%.c include/expander.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/stringbuilder/%.c include/stringbuilder.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/error/%.c include/error.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/heredoc/%.c include/heredoc.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/signals/%.c include/signals.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: src/hacks/%.c include/hacks.h $(GLOBAL_HEADERS)
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
