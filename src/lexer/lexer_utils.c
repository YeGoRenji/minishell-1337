/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:54:59 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/19 21:00:07 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	print_substr(int start, int end, char *str)
{
	while (start < end)
		printf("%c", str[start++]);
}

bool	is_word(char c)
{
	// TODO : Check if there are other chars for WORD
	return (ft_isalnum(c) || c == '/' || c == '-'
		|| c == '_' || c == '.' || c == '*' || c == '$');
}

t_token_type	get_token_type(char *str)
{
	if (is_word(str[0]))
		return (WORD);
	if (ft_iswhitespace(str[0]))
		return (WHITE_SPACE);
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

int	count_with_func(char *str, bool (*test_func)(char))
{
	int	len;

	len = 0;
	while (test_func(*str++))
		len++;
	return (len);
}

int	get_token_len(t_token_type type, char *str)
{
	char	*lengths;
	char	*pos;

	lengths = "\0\0\0\1\2\1\2\1\1\1\2\0";
	if ((int)type < 0)
		return (1);
	if (lengths[type] > 0)
		return (lengths[type]);
	if (type == WORD)
		return (count_with_func(str, is_word));
	if (type == WHITE_SPACE)
		return (count_with_func(str, ft_iswhitespace));
	if (type == DQSTR)
		pos = ft_strchr(str + 1, '"');
	else
		pos = ft_strchr(str + 1, '\'');
	// TODO : This is Unclosed Quote Error !
	if (pos == NULL)
		return (1);
	// TODO : return the content without ' or "
	return (pos - str + 1);
}
