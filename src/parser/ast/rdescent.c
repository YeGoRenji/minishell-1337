/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdescent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 03:58:11 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/11 15:37:47 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

t_ast_cmd	*parse_parenths(t_token **current)
{
	t_ast_cmd	*node;

	node = NULL;
	if (match(*current, (t_token_type[]){LPREN}, 1))
	{
		advance(current);
		node = parse_cmd(current);
		if (!node || !match(*current, (t_token_type[]){RPREN}, 1))
			return (free_ast(node), NULL);
		advance(current);
	}
	node = subsh_node(node);
	if (!node)
		return (free_ast(node), NULL);
	return (node);
}

bool	parse_term(t_token **current, t_ast_cmd *sub_sh,
	t_token **exe_lst, t_ast_redir **redir_lst)
{
	t_ast_cmd	*node;

	if (match(*current, (t_token_type[]){WORD, STR, DQSTR}, 3))
	{
		if (sub_sh)
			return (false);
		ft_tokadd_back(exe_lst, clone_tok(*current));
	}
	else
	{
		node = redir_file(current);
		if (!node)
			return (false);
		add_redir_node(redir_lst, node);
	}
	return (true);
}

t_ast_cmd	*parse_redir(t_token **current)
{
	t_ast_cmd	*sub_sh;
	t_token		*exe_lst;
	t_ast_redir	*redir_lst;

	sub_sh = NULL;
	exe_lst = NULL;
	redir_lst = NULL;
	if (match(*current, (t_token_type[]){LPREN}, 1))
	{
		sub_sh = parse_parenths(current);
		if (!sub_sh)
			return (NULL);
	}
	while (match(*current, (t_token_type[]){
			WORD, STR, DQSTR, OUTPUT, APPEND, INPUT, HEREDOC}, 7))
	{
		if (!parse_term(current, sub_sh, &exe_lst, &redir_lst))
			return (free_redir(sub_sh, redir_lst, exe_lst), NULL);
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
	while (match(*current, (t_token_type[]){PIPE}, 1))
	{
		advance(current);
		next_node = parse_redir(current);
		if (!next_node)
			return (free_ast(node), NULL);
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
	while (match(*current, (t_token_type[]){AND, OR}, 2))
	{
		is_or = ((*current)->type == OR);
		advance(current);
		next_node = parse_pipe(current);
		if (!next_node)
			return (free_ast(node), NULL);
		node = binary_node(!is_or * P_AND + is_or * P_OR, node, next_node);
	}
	return (node);
}
