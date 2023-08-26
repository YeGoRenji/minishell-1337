/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdescent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 03:58:11 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/26 18:57:21 by ylyoussf         ###   ########.fr       */
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

bool	add_redir_node(t_ast_redir **lst, t_ast_cmd *node)
{
	t_ast_redir	*tmp;

	if (!lst || !node)
		return (false);
	if (!(*lst))
	{
		*lst = (t_ast_redir *)node;
		return (true);
	}
	tmp = *lst;
	while (tmp && tmp->cmd)
		tmp = (t_ast_redir *)(tmp)->cmd;
	tmp->cmd = node;
	return (true);
}

void	free_redir(t_ast_cmd *sub_sh, t_ast_redir *redir_lst, t_token *exe_lst)
{
	free_ast(sub_sh);
	free_ast((t_ast_cmd *)redir_lst);
	free_tok_lst(exe_lst);
}

t_ast_cmd	*parse_redir(t_token **current)
{
	t_ast_cmd	*node;
	t_ast_cmd	*sub_sh;
	t_token		*exe_lst;
	t_ast_redir	*redir_lst;

	sub_sh = NULL;
	exe_lst = NULL;
	redir_lst = NULL;
	if ((*current)->type == LPREN)
	{
		sub_sh = parse_parenths(current);
		if (!sub_sh)
			return (NULL);
	}
	// TODO : Stop spaghetti code ?
	while (*current && WORD <= (*current)->type && (*current)->type <= HEREDOC)
	{
		if (OUTPUT <= (*current)->type && (*current)->type <= HEREDOC)
		{
			node = redir_file(current);
			if (!node)
				return (free_redir(sub_sh, redir_lst, exe_lst), NULL);
			add_redir_node(&redir_lst, node);
		}
		else
		{
			if (sub_sh)
				return (free_redir(sub_sh, redir_lst, exe_lst), NULL);
			ft_tokadd_back(&exe_lst, clone_tok(*current));
		}
		advance(current);
	}
	if (exe_lst && !sub_sh)
		sub_sh = exec_node(exe_lst);
	add_redir_node(&redir_lst, sub_sh);
	return ((t_ast_cmd *)redir_lst);
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
