/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:18:58 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/17 15:21:57 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:52:58 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/17 14:50:51 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_utils.h"

int	export(int argc, char **argv, t_env **env)
{
	int		i;
	char	*ptr;
	char	*key;
	int		res;

	if (!env)
		return (1);
	if (!argc)
		return (print_exports(*env));
	i = 0;
	res = 0;
	while (i < argc)
	{
		ptr = argv[i++];
		if (validate_arg(ptr))
		{
			res = 1;
			continue ;
		}
		if (handle_concate_case(ptr))
			continue ;
		key = get_key(ptr);
		set_env_value(key, get_value(ptr), !!ft_strchr(ptr, '='));
	}
	return (res);
}

int	handle_concate_case(char *line)
{
	if (!line || !is_concate(line))
		return (0);
	concate_env(get_key(line), get_value(line));
	return (1);
}
