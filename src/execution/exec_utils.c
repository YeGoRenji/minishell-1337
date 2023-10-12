/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:09:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/12 18:52:36 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <errno.h>

int	print_err(char *preced, int msg_code)
{
	t_strbuilder	*sb;

	sb = stringbuilder();
	sb_append(sb_append(sb, "shell69: "), preced);
	if (msg_code == -1)
		(sb_append(sb, ": command not found\n"), set_exit_status(127));
	else if (msg_code == -69)
		(sb_append(sb, ": Is a directory\n"), set_exit_status(126));
	else if (msg_code == -2)
		sb_append(sb, ": allocation error\n");
	else if (msg_code == -3)
		sb_append(sb, ": $PATH var unset\n");
	else if (msg_code == -4)
		(sb_append(sb, ": ambiguous redirect\n"), set_exit_status(1));
	else if (msg_code == -5)
		(sb_append(sb, ": No such file or directory\n"), set_exit_status(1));
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

	node = search_in_env(envp, ft_strdup("PATH"));
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
	char			*path_val;
	char			**paths[2];
	t_strbuilder	*sb;
	char			**envp;

	if (is_dir(cmd[0]))
		return (-69);
	if (ft_strchr(cmd[0], '/'))
	{
		if (check_file(cmd[0], X_OK))
		{
			envp = consume_env(get_envp(NULL));
			return (execve(cmd[0], cmd, envp), free_list(envp), -1);
		}
		if (errno == ENOTDIR)
			exit(126);
		else
			exit(127);
		// TODO : ben 10 and the pursuite of other cases
	}
	path_val = find_path(env);
	if (!path_val)
		return (-3);
	paths[0] = ft_split(path_val, ':');
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
		{
			envp = consume_env(get_envp(NULL));
			if (execve(*paths[0], cmd, envp) == -1)
				return (free_list(envp), free_list(paths[1]), -1);
		}
		paths[0]++;
	}
	return (free_list(paths[1]), -1);
}
