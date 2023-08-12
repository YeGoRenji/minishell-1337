/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdescent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 03:58:11 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/12 03:58:37 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_ast_cmd	*parse_redir(t_token **current)
{
	t_ast_cmd	*node;
	t_token		*lst;
	t_ast_redir	*downwords;

	if (!*current)
		return (NULL);

	if (!(WORD <= (*current)->type && (*current)->type <= HEREDOC))
		return (NULL);
	// TODO : Stop spaggeti code ?
	lst = NULL;
	downwords = NULL;
	while (*current && WORD <= (*current)->type && (*current)->type <= HEREDOC)
	{
		if (OUTPUT <= (*current)->type && (*current)->type <= HEREDOC)
		{
			if (!(*current)->next || !(WORD <= (*current)->next->type && (*current)->next->type <= DQSTR))
				return (NULL); // ! (EXPECTED file after redir) Free
			if (!downwords)
			{
				node = (t_ast_cmd *)tok_to_redir(*current);
				downwords = (t_ast_redir *)node;
			}
			else
			{
				downwords->cmd = (t_ast_cmd *)tok_to_redir(*current);
				downwords = (t_ast_redir *)downwords->cmd;
			}
			advance(current);
		}
		else
			ft_tokadd_back(&lst, clone_tok(*current));
		advance(current);
	}
	if (!lst)
		return (NULL); // ! (EXPECTED EXEC) Free
	if (downwords)
		downwords->cmd = exec_node(lst);
	else
		node = exec_node(lst);
	return (node);
}

t_ast_cmd	*parse_parenths(t_token **current)
{
	t_ast_cmd	*node;

	node = NULL;
	if (*current && (*current)->type == LPREN)
	{
		advance(current);
		node = parse_cmd(current);
		if (!node || !*current || (*current)->type != RPREN)
			return (free(node), NULL);
		advance(current);
	}
	return (node);
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
		if (*current && (*current)->type == LPREN)
			next_node = parse_parenths(current);
		else
			next_node = parse_redir(current);
		if (!next_node)
			return (free(node), NULL); // ! (EXPECTED Expr after PIPE)
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
	if (*current && (*current)->type == LPREN)
		node = parse_parenths(current);
	else if (*current)
		node = parse_pipe(current);
	while (*current && ((*current)->type == AND || (*current)->type == OR))
	{
		is_or = ((*current)->type == OR);
		advance(current);
		if (*current && (*current)->type == LPREN)
			next_node = parse_parenths(current);
		else
			next_node = parse_pipe(current);
		// ! Freeing a tree is not this simple lol
		// TODO : implement recursive free function
		// TODO : Error info in the node struct maybe ?
		if (!next_node)
			return (free(node), NULL); // ! (EXPECTED Expr after conditional)
		node = binary_node(!is_or * P_AND + is_or * P_OR, node, next_node);
	}
	return (node);
}

