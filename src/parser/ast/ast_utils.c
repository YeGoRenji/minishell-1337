/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 03:58:53 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/22 21:19:50 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include <stdbool.h>

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

t_token	*clone_tok(t_token *tok)
{
	t_token	*clone;
	t_token *no_space;

	if (!tok)
		return (NULL);
	clone = new_token(tok->type, ft_strdup(tok->value), tok->len);
	clone->to_expand = tok->to_expand;
	no_space = tok->nospace_next;
	while (no_space)
	{
		ft_tokadd_back(&clone->nospace_next, clone_tok(no_space));
		no_space = no_space->nospace_next;
	}
	return (clone);
}

t_ast_redir *tok_to_redir(t_token *redir_ptr)
{
	int			fd;
	int			mode;
	t_ast_redir	*redir;

	mode = 0;
	fd = 0;
	mode |= (redir_ptr->type == HEREDOC) * (O_CREAT | O_RDWR);
	mode |= (redir_ptr->type == INPUT) * (O_RDONLY);
	mode |= (redir_ptr->type == OUTPUT) * (O_CREAT | O_WRONLY);
	mode |= (redir_ptr->type == APPEND) * (O_CREAT | O_APPEND);
	fd += (redir_ptr->type == OUTPUT || redir_ptr->type == APPEND);
	redir = (t_ast_redir *)redir_node(
		redir_ptr->type,
		clone_tok(redir_ptr->next),
		mode,
		fd,
		NULL);
	return (redir);
}

bool	valid_file_tok(t_token **current)
{
	if (!(*current))
		return (false);
	return (WORD <= (*current)->next->type && (*current)->next->type <= DQSTR);
}