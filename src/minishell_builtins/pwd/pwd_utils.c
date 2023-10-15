/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:38:45 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/12 18:44:26 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global_utils.h"

char	*pwd_trolling(char *str)
{
	static char	*pwd;

	if (!str)
		return (pwd);
	if (pwd)
		set_env_value(ft_strdup("OLDPWD"), ft_strdup(pwd), 1);
	free(pwd);
	pwd = trim_path(str);
	set_env_value(ft_strdup("PWD"), ft_strdup(pwd), 1);
	return (pwd);
}

char	*trim_path(char *pwd)
{
	size_t	pwd_len;
	size_t	i;
	size_t	fake_i;
	char	*buff;

	pwd_len = ft_strlen(pwd);
	if (ft_strlen(pwd) == 1)
		return (ft_strdup(pwd));
	buff = malloc((pwd_len + 1) * sizeof(char));
	i = 0;
	fake_i = 0;
	while (fake_i < pwd_len)
	{
		if (pwd[fake_i] == '/' && pwd[fake_i + 1] == '/')
		{
			fake_i++;
			continue ;
		}
		buff[i++] = pwd[fake_i++];
	}
	buff[i--] = 0;
	if (ft_strlen(buff) > 1 && buff[i] == '/')
		buff[i] = '\0';
	return (buff);
}
