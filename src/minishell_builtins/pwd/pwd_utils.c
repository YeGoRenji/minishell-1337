/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:38:45 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 16:38:42 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global_utils.h"

char	*pwd_trolling(char *str)
{
	static char	*pwd;
	t_env		*env;
	t_env		*pwd_node;

	if (!str)
		return (pwd);
	env = get_envp(NULL);
	pwd_node = search_in_env(env, "PWD");
	if (pwd_node)
		set_env_value(ft_strdup("OLDPWD"), ft_strdup(pwd_node -> value), 1);
	else
		set_env_value(ft_strdup("OLDPWD"), ft_strdup(""), 1);
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
	buff = ft_malloc((pwd_len + 1) * sizeof(char));
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
