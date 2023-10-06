/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/06 14:20:17 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"
# include "lexer.h"

typedef enum e_node_type
{
	P_AND,
	P_OR,
	P_PIPE,
	P_EXEC,
	P_REDIR,
	P_SUBSH
}	t_node_type;

typedef struct s_cmd
{
	t_node_type		type;
}	t_ast_cmd;

typedef struct s_ast_binary
{
	t_node_type		type;
	t_ast_cmd		*left;
	t_ast_cmd		*right;
}	t_ast_binary;

typedef struct s_ast_exec
{
	t_node_type		type;
	t_token			*argv_tok;
}	t_ast_exec;

typedef struct s_ast_redir
{
	t_node_type		type;
	t_token_type	direction;
	t_token			*file_tok;
	int				mode;
	int				fd;
	t_ast_cmd		*cmd;
}	t_ast_redir;

typedef struct s_ast_subsh
{
	t_node_type		type;
	t_ast_cmd		*cmd;
}	t_ast_subsh;

t_ast_cmd	*parse_cmd(t_token **current);
// data
t_ast_cmd	*binary_node(t_node_type type, t_ast_cmd *left, t_ast_cmd *right);
t_ast_cmd	*exec_node(t_token *argv_tok);
t_ast_cmd	*redir_node(t_token_type direction, t_token *file_tok,
				int mode_fd[2], t_ast_cmd *cmd);
t_ast_cmd	*subsh_node(t_ast_cmd *cmd);
// utils
void		advance(t_token **current);
bool		match(t_token *tok, t_token_type types[], int size);
t_token		*clone_tok(t_token *tok);
t_ast_redir	*tok_to_redir(t_token *redir_ptr);
void		free_ast(t_ast_cmd *tree);
void		free_tok_lst(t_token *tok);
void		print_nosp_tok(FILE *f, t_token *tok); // ? Debug

#endif // AST_H
