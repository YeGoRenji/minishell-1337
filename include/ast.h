/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/22 02:56:55 by ylyoussf         ###   ########.fr       */
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

typedef struct s_ast_and
{
	t_node_type		type;
	t_ast_cmd		*left;
	t_ast_cmd		*right;
} t_ast_and;

typedef struct s_ast_or
{
	t_node_type		type;
	t_ast_cmd		*left;
	t_ast_cmd		*right;
} t_ast_or;

typedef struct s_ast_pipe
{
	t_node_type		type;
	t_ast_cmd		*left;
	t_ast_cmd		*right;
} t_ast_pipe;

typedef struct s_ast_exec
{
	t_node_type		type;
	char			**argv;
} t_ast_exec;

typedef struct s_ast_redir
{
	t_node_type		type;
	char			*file;
	int				mode;
	int				fd;
	t_ast_cmd		*cmd;
} t_ast_redir;

t_ast_cmd	*parse_cmd(t_list *lst_tok, t_list *lst_end);

#endif // AST_H
