/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/22 21:20:18 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "libft.h"
#include "lexer.h"

typedef enum e_node_type
{
	P_AND,
	P_OR,
	P_PIPE,
	P_EXEC,
	P_REDIR
}	t_node_type;

typedef struct s_cmd
{
	t_node_type		type;
} t_ast_cmd;

typedef struct s_ast_binary
{
	t_node_type		type;
	t_ast_cmd		*left;
	t_ast_cmd		*right;
} t_ast_binary;

typedef struct s_ast_exec
{
	t_node_type		type;
	t_token			*argv_tok;
} t_ast_exec;

typedef struct s_ast_redir
{
	t_node_type		type;
	// Just for debug Maybe
	t_token_type	direction;
	t_token			*file_tok;
	int				mode;
	int				fd;
	t_ast_cmd		*cmd;
} t_ast_redir;

t_ast_cmd	*parse_cmd(t_token **current);
// data
t_ast_cmd	*binary_node(t_node_type type, t_ast_cmd *left, t_ast_cmd *right);
t_ast_cmd	*exec_node(t_token *argv_tok);
t_ast_cmd	*redir_node(t_token_type direction, t_token *file_tok, int mode, int fd, t_ast_cmd *cmd);
// utils
void		advance(t_token **current);
bool 		match(t_token *tok, t_token_type types[]);
t_token		*clone_tok(t_token *tok);
t_ast_redir	*tok_to_redir(t_token *redir_ptr);
bool		valid_file_tok(t_token **current);

#endif // AST_H
