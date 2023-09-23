/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:44:53 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/23 14:46:09 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <expander.h>

bool	wild_match(char *str, char *expr)
{
	while (*str && *expr)
	{
		if (*expr == '*' && expr[1] == '\0')
			return (true);
		if (*expr == '*')
		{
			while (expr[1] == '*')
				expr++;
			if (wild_match(str + (expr[1] != *str), 
			 expr + (expr[1] == str[1] || expr[1] == *str)))
			return (true);
		}
		if (*str != *expr)
			return (false);
		str++;
		expr++;
	}
	return (*str == '\0' && *expr == '\0');
}

