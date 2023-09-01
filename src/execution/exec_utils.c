/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:09:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/09/01 02:48:34 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

int	print_err(char *preced, int msg_code)
{
	t_strbuilder	*sb;

	sb = stringbuilder();
	sb_append(sb_append(sb, "shell69: "), preced);
	if (msg_code == -1)
		sb_append(sb, ": command not found\n");
	else if (msg_code == -2)
		sb_append(sb, ": allocation error\n");
	else if (msg_code == -3)
		sb_append(sb, ": $PATH var unset\n");
	if (msg_code == 0)
		perror(sb->str);
	else
		ft_putstr_fd(sb->str, 2);
	sb_free(sb);
	return (msg_code);
}

int	check_file(char *file_path, int access_type)
{
	if (access(file_path, access_type) != 0)
	{
		print_err(file_path, 0);
		return (0);
	}
	return (1);
}

char	*find_path(t_env *envp)
{
	t_env	*node;

	node = search_in_env(envp, "PATH");
	if (!node)
		return (NULL);
	return (node->value);
}


int	check_cmd(char **cmd, t_env *env)
{
	char			*path_var;
	char			**paths[2];
	t_strbuilder	*sb;
	char			**envp;

	if (ft_strchr(cmd[0], '/'))
	{
		if (check_file(cmd[0], X_OK))
		{
			envp = consume_env(get_envp(NULL));
			return (execve(cmd[0], cmd, envp), free_list(envp), -1);
		}
		exit(-1);
	}
	path_var = find_path(env);
	if (!path_var)
		return (-3);
	paths[0] = ft_split(path_var + 5, ':');
	paths[1] = paths[0];
	if (!paths[0])
		return (-2);
	while (*paths[0])
	{
		sb = stringbuilder();
		sb_append(sb_append(sb_append_free(sb, *paths[0]), "/"), cmd[0]);
		*paths[0] = sb->str;
		free(sb);
		if (access(*paths[0], X_OK) == 0)
			if (execve(*paths[0], cmd, consume_env(get_envp(NULL))) == -1)
				return (-1);
		free(*paths[0]++);
	}
	return (free(paths[1]), -1);
}
