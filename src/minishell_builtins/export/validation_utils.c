/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:24:22 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/16 02:10:38 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_utils.h"

int	validate_arg(char *arg)
{
	if (!arg)
		return (false);
	if (validate_var_name(arg))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	return (0);
}

int	ft_is_alphanum_underscore(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		str++;
	}
	return (0);
}

int	validate_var_name(char *str)
{
	char	*key;
	size_t	split_index;
	int		res;

	if (!str || is_bad_env_name_start(str[0]))
		return (1);
	split_index = 0;
	if (is_concate(str))
		split_index = (size_t)ft_strchr(str, '+') - (size_t)str;
	else if (ft_strchr(str, '='))
		split_index = (size_t)ft_strchr(str, '=') - (size_t)str;
	if (split_index)
		key = ft_substr(str, 0, split_index);
	else
		key = ft_strdup(str);
	res = ft_is_alphanum_underscore(key + 1);
	free(key);
	return (res);
}

int	is_bad_env_name_start(char c)
{
	return (!ft_isalpha(c) && (c != '_'));
}
