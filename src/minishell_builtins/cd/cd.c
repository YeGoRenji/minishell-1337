/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:20:46 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 13:37:20 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_utils.h"
#include <stdio.h>

int	cd(char *arg, t_env *env)
{
	t_env	*node;

	if (!arg)
	{
		node = search_in_env(env, "HOME");
		if (!node)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		else
			return (change_directory(node->value));
	}
	else
		return (change_directory(arg));
}
