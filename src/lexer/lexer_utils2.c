/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:28:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/20 01:53:50 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

bool	valid_env_char(char c)
{
	return (ft_isalpha(c) || ft_strchr("?_", c));
}

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
	if (dollar_pos && valid_env_char(dollar_pos[1]))
		return (true);
	if (wild_pos)
		return (true);
	return (false);
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
