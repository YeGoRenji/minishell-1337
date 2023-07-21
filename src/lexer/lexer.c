/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 04:49:35 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/21 01:43:09 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

bool	check_expanding(char *str, t_token_type type)
{
	char	*wild_pos;
	char	*dollar_pos;

	wild_pos = NULL;
	if (type != DQSTR)
		wild_pos = ft_strchr(str, '*');
	dollar_pos = ft_strchr(str, '$');
	if (!wild_pos && !dollar_pos)
		return (false);
	if (dollar_pos && ft_isalpha(dollar_pos[1]))
		return (true);
	if (wild_pos)
		return (true);
	return (false);
}

t_token	*new_token(t_token_type type, char *value, int len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->len = len;
	token->to_expand = false;
	if (type == DQSTR || type == WORD)
		token->to_expand = check_expanding(value, type);
	token->nospace_next = NULL;
	return (token);
}

void print_token(void *token) // Debug !
{
	t_token *tok = (t_token *)token;
	const char *token_types[] = { // Debug !
		"WORD",
		"STR",
		"DQSTR",
		"OUTPUT",
		"APPEND",
		"INPUT",
		"HEREDOC",
		"LPREN",
		"RPREN",
		"PIPE",
		"OR",
		"AND",
		"WHITE_SPACE"
	};

	while (tok)
	{
		printf("[%s(%d)] %s%s", token_types[tok->type], tok->len, tok->value, tok->to_expand ? " EXPAND !" : "");
		if (tok->nospace_next)
			printf(" -> ");
		tok = tok->nospace_next;
	}
	printf("\n");
}

void	add_sub_sublist(t_token **list, t_token *new_tok)
{
	t_token	*ptr;

	if (!*list)
	{
		*list = new_tok;
		return ;
	}
	ptr = *list;
	while (ptr->nospace_next)
		 ptr = ptr->nospace_next;
	ptr->nospace_next = new_tok;
}

bool add_token(t_list **tokens, t_token *token, bool is_space)
{
	t_list	*new_tok;
	t_list	*last_tok_node;
	t_token	*last_tok;

	if (!token)
		return (false);
	last_tok_node = ft_lstlast(*tokens);
	last_tok = NULL;
	if (last_tok_node)
		last_tok = last_tok_node->content;
	if (!last_tok_node || is_space || last_tok->type >= OUTPUT 
		|| token->type >= OUTPUT)
	{
		new_tok = ft_lstnew(token);
		if (!new_tok)
			return (false);
		return (ft_lstadd_back(tokens, new_tok), true);
	}
	add_sub_sublist(&last_tok->nospace_next, token);
	return (true);
}

bool	lexer(char *command_line, t_list **tokens)
{
	int		index;
	bool	space;
	t_token this_tok;

	index = 0;
	*tokens = NULL;
	space = true;
	this_tok.type = WHITE_SPACE;
	while (command_line[index])
	{
		space = this_tok.type == WHITE_SPACE;
		this_tok.type = get_token_type(command_line + index);
		this_tok.len = get_token_len(this_tok.type, command_line + index);
		if ((int)this_tok.type >= 0 && this_tok.type != WHITE_SPACE)
		{
			this_tok.value = ft_substr(command_line, index, this_tok.len);
			if (!this_tok.value)
				return (false);
			add_token(tokens,
				new_token(this_tok.type, this_tok.value, this_tok.len)
				, space);
		}
		else if (this_tok.type != WHITE_SPACE)
			printf("[%s] %c\n", "UNKNOWN", command_line[index]); // Debug !
		index += this_tok.len;
	}
	ft_lstiter(*tokens, print_token); // Debug !
	return (1);
}
