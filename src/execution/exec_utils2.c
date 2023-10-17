/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:01:03 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/17 14:46:34 by afatimi          ###   ########.fr       */
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

/* TODO : ben 10 and the pursuite of other cases */
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
		else
			exit(126);
		if (errno == ENOTDIR)
			exit(126);
		else
			exit(127);
	}
	return (false);
}

char	*check_file_tok(t_token *file_tok)
{
	char	**expanded;
	char	*file_name;
	int		len;

	expanded = expand_args(file_tok);
	if (!expanded)
		return (set_exit_status(1), NULL);
	len = split_len(expanded);
	if (len == 0)
		return (free_list(expanded), set_exit_status(1), NULL);
	if (len > 1 || (*file_tok->value == '$' && len == 1 && **expanded == '\0'))
		return (print_err(file_tok->value, -4), free_list(expanded), NULL);
	file_name = ft_strdup(*expanded);
	free_list(expanded);
	return (file_name);
}
