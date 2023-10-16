/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:33:33 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/16 02:05:13 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset_utils.h"

int	unset(int argc, char **args, t_env **env)
{
	char	*ptr;
	int		i;

	if (!args || !env)
		return (1);
	i = 0;
	while (i < argc)
	{
		ptr = args[i++];
		if (validate_arg(ptr))
			continue;
		del_from_env(env, ptr);
	}
	return (0);
}
