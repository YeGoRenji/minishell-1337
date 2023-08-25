/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:54:59 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/25 18:45:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	print_substr(int start, int end, char *str) // ? Debug !
{
	while (start < end)
		printf("%c", str[start++]);
}

bool	str_contains(char *str, char c)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

bool	not_special(char c)
{
	if (c == '\0' || ft_iswhitespace(c))
		return (false);
	return (!str_contains("|\'\"><()&", c));
}

t_token_type	get_token_type(char *str)
{
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
	if (str[0] == '&')
	{
		if (str[1] == '&')
			return (AND);
		return (-1);
	}
	return (WORD);
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

	lengths = "\0\0\0\1\2\1\2\1\1\1\2\2\0";
	if ((int)type < 0)
		return (1);
	if (lengths[type] > 0)
		return (lengths[type]);
	if (type == WORD)
	{
		if (str[0] == '$' && str[1] == '?')
			return (2);
		return (count_with_func(str, not_special));
	}
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

void	free_tok_lst(t_token *tok)
{
	t_token	*tmp;

	if (!tok)
		return ;
	while (tok)
	{
		printf("Freeing %s\n", tok->value);
		free(tok->value);
		free_tok_lst(tok->nospace_next);
		tmp = tok;
		tok = tok->next;
		free(tmp);
	}
}