/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:09:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/17 15:00:22 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		print_err("fork", 0);
		exit(1);
	}
	return (pid);
}

char	*find_path(t_env *envp)
{
	t_env	*node;

	node = search_in_env(envp, "PATH");
	if (!node)
		return (NULL);
	return (node->value);
}

int	is_dir(char *str)
{
	DIR	*ptr;
	int	res;

	if (!str)
		return (0);
	ptr = opendir(str);
	res = !!ptr;
	if (ptr)
		closedir(ptr);
	return (res);
}

int	execute_cmd(char **cmd, t_env *env)
{
	char			**paths;
	char			**tmp;
	t_strbuilder	*sb;

	if (is_dir(cmd[0]))
		return (-69);
	if (check_absolute_path(cmd, env))
		return (-1);
	if (!find_path(env))
		return (-3);
	paths = ft_split(find_path(env), ':');
	tmp = paths;
	if (!paths)
		return (-2);
	while (*tmp)
	{
		sb = stringbuilder();
		sb_append(sb_append(sb_append_free(sb, *tmp), "/"), cmd[0]);
		*tmp = sb->str;
		free(sb);
		if (check_if_executable(cmd, *tmp, paths, env))
			return (-1);
		tmp++;
	}
	return (free_list(paths), -1);
}
