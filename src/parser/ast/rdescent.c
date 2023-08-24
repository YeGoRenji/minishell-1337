/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdescent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 03:58:11 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/24 13:49:15 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_ast_cmd	*parse_parenths(t_token **current)
{
	t_ast_cmd	*node;

	node = NULL;
	if (*current && (*current)->type == LPREN)
	{
		advance(current);
		node = parse_cmd(current);
		if (!node || !*current || (*current)->type != RPREN)
			return (free_ast(node), NULL);
		advance(current);
	}
	node = subsh_node(node);
	if (!node)
		return (free_ast(node), NULL);
	return (node);
}

t_ast_cmd	*redir_file(t_token **current)
{
	t_ast_cmd	*node;
	t_token		*start;

	node = NULL;
	if (OUTPUT <= (*current)->type && (*current)->type <= HEREDOC)
	{
		start = *current;
		advance(current);
		if (!valid_file_tok(current))
			return (NULL); // ! (EXPECTED file after redir) Free
		node = (t_ast_cmd *)tok_to_redir(start);
	}
	return (node);
}

t_ast_cmd	*parse_redir(t_token **current)
{
	t_ast_cmd	*node;
	t_ast_cmd	*to_return;
	t_ast_cmd	*exe;
	t_token		*lst;
	t_ast_redir	*downwords;

	exe = NULL;
	lst = NULL;
	downwords = NULL;
	to_return = NULL;
	if ((*current)->type == LPREN)
	{
		exe = parse_parenths(current);
		if (!exe)
			return (NULL);
	}
	// TODO : Stop spaghetti code ?
	while (*current && WORD <= (*current)->type && (*current)->type <= HEREDOC)
	{
		if (OUTPUT <= (*current)->type && (*current)->type <= HEREDOC)
		{
			node = redir_file(current);
			if (!node)
				return (free_ast(to_return), free_tok_lst(lst), NULL);
			if (downwords)
				downwords->cmd = node;
			else
				to_return = node;
			downwords = (t_ast_redir *)node;
		}
		else
			ft_tokadd_back(&lst, clone_tok(*current));
		advance(current);
	}
	if (lst && !exe)
		exe = exec_node(lst);
	if (downwords)
		downwords->cmd = exe;
	else
		to_return = exe;
	return (to_return);
}

t_ast_cmd	*parse_pipe(t_token **current)
{
	t_ast_cmd	*node;
	t_ast_cmd	*next_node;

	node = parse_redir(current);
	if (!node)
		return (NULL);
	while (*current && (*current)->type == PIPE)
	{
		advance(current);
		next_node = parse_redir(current);
		if (!next_node)
			return (free_ast(node), NULL); // ! (EXPECTED Expr after PIPE)
		node = binary_node(P_PIPE, node, next_node);
	}
	return (node);
}

t_ast_cmd	*parse_cmd(t_token **current)
{
	t_ast_cmd	*node;
	t_ast_cmd	*next_node;
	bool		is_or;

	node = NULL;
	if (!*current)
		return (NULL);
	node = parse_pipe(current);
	if (!node)
		return (NULL);
	while (*current && ((*current)->type == AND || (*current)->type == OR))
	{
		is_or = ((*current)->type == OR);
		advance(current);
		next_node = parse_pipe(current);
		// ! Freeing a tree is not this simple lol
		// TODO : implement recursive free function
		if (!next_node)
			return (free_ast(node), NULL); // ! (EXPECTED Expr after conditional)
		node = binary_node(!is_or * P_AND + is_or * P_OR, node, next_node);
	}
	return (node);
}
