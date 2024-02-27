/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:32:00 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/02/27 17:46:40 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parser(t_token *tokens, char *cmd, t_ast_cmd **tree)
{
	t_token		*current;

	*tree = NULL;
	if (!tokens)
		return (false);
	current = tokens;
	if (current->type == NEW_LINE)
		return (free_tok_lst(tokens), true);
	*tree = parse_cmd(&current);
	if (!(*tree) || current->type != NEW_LINE)
	{
		syntax_error(current->value);
		return (free_tok_lst(tokens), false);
	}
	free_tok_lst(tokens);
	debug_ast(*tree, cmd);
	return (patch_heredoc(*tree));
}
