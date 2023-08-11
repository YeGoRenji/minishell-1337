/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 04:12:02 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/11 06:09:00 by ylyoussf         ###   ########.fr       */
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

void	advance(t_token **current)
{
	*current = (*current)->next;
}

bool match(t_token *tok, t_token_type types[])
{
	if (!tok)
		return false;
	while ((int)*types != -1)
	{
		if (tok->type == *types)
			return true;
		types++;
	}
	return false;
}

t_ast_cmd	*parse_redir(t_token **current)
{
	t_ast_cmd	*node;
	t_token		*new;
	t_token		*lst;

	if (!*current)
		return (NULL);

	if (!match(*current, (t_token_type[]) {WORD, HEREDOC, INPUT, OUTPUT, APPEND, -1}))
		return (NULL);
	lst = NULL;
	// TODO : actual Redirections
	while (match(*current, (t_token_type[]) {WORD, HEREDOC, INPUT, OUTPUT, APPEND, -1}))
	{
		new = new_token((*current)->type, ft_strdup((*current)->value), (*current)->len);
		ft_tokadd_back(&lst, new);
		advance(current);
	}
	node = exec_node(lst);
	return (node);
}

t_ast_cmd	*parse_pipe(t_token **current)
{
	t_ast_cmd	*node;
	t_ast_cmd	*next_node;

	node = parse_redir(current);
	
	while (*current && (*current)->type == PIPE)
	{
		advance(current);
		if (*current && (*current)->type == LPREN)
			next_node = parse_cmd(current);
		else
			next_node = parse_redir(current);
		if (!next_node)
			return (free(node), NULL);
		node = binary_node(P_PIPE, node, next_node);
	}

	return (node);
}

t_ast_cmd	*parse_cmd(t_token **current)
{
	t_ast_cmd	*node;
	t_ast_cmd	*next_node;
	bool		and_or;

	node = NULL;
	if (!*current)
		return (NULL);
	if (*current && (*current)->type == LPREN)
	{
		advance(current);
		node = parse_cmd(current);
		if (!node || !*current || (*current)->type != RPREN)
			return (free(node), NULL);
		advance(current);
	}
	else if (*current)
		node = parse_pipe(current);
	while (*current && ((*current)->type == AND || (*current)->type == OR))
	{
		and_or = ((*current)->type == OR);
		advance(current);
		if (*current && (*current)->type == LPREN)
			next_node = parse_cmd(current);
		else
			next_node = parse_pipe(current);
		// ! Freeing a tree is not this simple lol
		if (!next_node)
			return (free(node), NULL);
		node = binary_node(!and_or * P_AND + and_or * P_OR, node, next_node);
	}
	return (node);
}

