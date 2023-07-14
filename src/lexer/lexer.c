/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 04:49:35 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/14 04:49:36 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void print_substr(int start, int end, char *str)
{
	while (start < end)
		printf("%c", str[start++]);
}

bool is_word(char c)
{
	// TODO : Check if there is other chars for WORD
	return (ft_isalnum(c) || c == '/' || c == '-' || c == '_');
}

t_token_type get_token_type(char *str)
{
	if (is_word(str[0]))
		return (WORD);
	if (str[0] == '|')
		return (PIPE + (str[1] == '|'));
	if (str[0] == '\'')
		return (STR);
	if (str[0] == '"')
		return (DQSTR);
	if (str[0] == '>')
		return (OUTPUT + (str[1] == '>'));
	if (str[0] == '<')
		return (INPUT + (str[1] == '<'));
	if (str[0] == '(')
		return (LPREN);
	if (str[0] == ')')
		return (RPREN);
	if (str[0] == '&' && str[1] == '&')
		return (AND);
	return (-1);
}

int	get_token_len(t_token_type type, char *str)
{
	int	lengths[] = { 
		-1, 
		-1, 
		-1, 
		1, 
		2, 
		1, 
		2, 
		1, 
		1, 
		1, 
		2, 
		2 
	};
	int	len;
	char *pos;

	if ((int)type < 0)
		return (1);
	if (lengths[type] > 0)
		return (lengths[type]);
	len = 0;
	if (type == WORD)
	{
		while (is_word(*str++))
			len++;
		return (len);
	}
	if (type == DQSTR)
		pos = ft_strchr(str + 1, '"');
	else
		pos = ft_strchr(str + 1, '\'');
	if (pos == NULL)
		return (1);
	return (pos - str + 1);
}

int lexer(char *command_line)
{
	const char *token_types[] = {
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
		"AND"
	};
	int current;

	current = 0;
	while (command_line[current])
	{
		int t = get_token_type(command_line + current);
		int len = get_token_len(t, command_line + current);
		if (t >= 0)
		{
			printf("[%s] ", token_types[t]);
			print_substr(current, current + len, command_line);
			printf("\n");
		}
		else
			if (command_line[current] != ' ')
				printf("[%s] %c\n", "UNKNOWN", command_line[current]);
		current += len;
	}
	return (1);
}
