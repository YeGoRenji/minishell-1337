/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 04:12:02 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/12 04:03:26 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_ast_cmd	*binary_node(t_node_type type, t_ast_cmd *left, t_ast_cmd *right)
{
	t_ast_binary	*node;

	node = malloc(sizeof(t_ast_binary));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*exec_node(t_token *argv_tok)
{
	t_ast_exec	*node;
	node = malloc(sizeof(t_ast_exec));
	if (!node)
		return (NULL);
	node->type = P_EXEC;
	node->argv_tok = argv_tok;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*redir_node(t_token_type direction, t_token *file_tok, int mode, int fd, t_ast_cmd *cmd)
{
	t_ast_redir	*node;
	node = malloc(sizeof(t_ast_redir));
	if (!node)
		return (NULL);
	node->type = P_REDIR;
	node->direction = direction;
	node->file_tok = file_tok;
	node->mode = mode;
	node->fd = fd;
	node->cmd = cmd;
	return ((t_ast_cmd *) node);
}

