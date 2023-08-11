/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/11 05:00:59 by ylyoussf         ###   ########.fr       */
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

#endif // AST_H
