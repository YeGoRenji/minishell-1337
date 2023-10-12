/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:01:03 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/12 21:02:02 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

static bool	check_file(char *file_path, int access_type)
{
	if (access(file_path, access_type) != 0)
	{
		print_err(file_path, 0);
		return (false);
	}
	return (true);
}

bool	check_if_executable(char **cmd, char *exec, char **paths, t_env *env)
{
	char			**envp;

	if (access(exec, X_OK) == 0)
	{
		envp = consume_env(env);
		if (execve(exec, cmd, envp) == -1)
			return (free_list(envp), free_list(paths), true);
	}
	return (false);
}

bool	check_absolute_path(char **cmd, t_env *env)
{
	char	**envp;

	if (ft_strchr(cmd[0], '/'))
	{
		if (check_file(cmd[0], X_OK))
		{
			envp = consume_env(env);
			return (execve(cmd[0], cmd, envp), free_list(envp), true);
		}
		if (errno == ENOTDIR)
			exit(126);
		else
			exit(127);
		// TODO : ben 10 and the pursuite of other cases
	}
	return (false);
}
