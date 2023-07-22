/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:25 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/22 01:05:08 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_ast_cmd	*and_node(t_ast_cmd *left, t_ast_cmd *right)
{
	t_ast_and	*node;
	node = malloc(sizeof(t_ast_and));
	if (!node)
		return (NULL);
	node->type = P_AND;
	node->left = left;
	node->right = right;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*or_node(t_ast_cmd *left, t_ast_cmd *right)
{
	t_ast_or	*node;
	node = malloc(sizeof(t_ast_or));
	if (!node)
		return (NULL);
	node->type = P_OR;
	node->left = left;
	node->right = right;
	return ((t_ast_cmd *) node);
}

t_ast_cmd	*pipe_node(t_ast_cmd *left, t_ast_cmd *right)
{
	t_ast_pipe	*node;
	node = malloc(sizeof(t_ast_pipe));
	if (!node)
		return (NULL);
	node->type = P_PIPE;
	node->left = left;
	node->right = right;
	return ((t_ast_cmd *) node);
}


t_ast_cmd	*exec_node()
{
	t_ast_exec	*node;
	node = malloc(sizeof(t_ast_exec));
	if (!node)
		return (NULL);
	node->type = P_EXEC;
	return ((t_ast_cmd *) node);
}


