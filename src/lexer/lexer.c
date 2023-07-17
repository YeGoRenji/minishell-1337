/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 04:49:35 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/17 16:35:20 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

bool	check_expanding(char *str)
{
	char	*wild_pos;
	char	*dollar_pos;

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
	token->to_expand = check_expanding(value);
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

	printf("[%s(%d)] %s%s\n", token_types[tok->type], tok->len, tok->value, tok->to_expand ? " EXPAND !" : "");
}

bool	lexer(char *command_line, t_list **tokens)
{
	int		current_token;
	int		len;
	int		current;
	char	*value;

	current = 0;
	*tokens = NULL;
	while (command_line[current])
	{
		current_token = get_token_type(command_line + current);
		len = get_token_len(current_token, command_line + current);
		if (current_token >= 0)
		{
			// TODO : check fails
			value = ft_substr(command_line, current, len);
			ft_lstadd_back(tokens, ft_lstnew(new_token(current_token, value, len)));
		}
		else
			printf("[%s] %c\n", "UNKNOWN", command_line[current]);
		current += len;
	}
	ft_lstiter(*tokens, print_token); // Debug !
	return (1);
}
