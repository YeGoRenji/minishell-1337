/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:09:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/31 22:25:29 by ylyoussf         ###   ########.fr       */
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
	while (envp)
	{
		if (ft_strncmp("PATH=", envp->value, 5) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}


int	check_cmd(char **cmd, t_env *envp)
{
	char			*path_var;
	char			**paths[2];
	t_strbuilder	*sb;

	if (ft_strchr(cmd[0], '/'))
	{
		if (check_file(cmd[0], X_OK))
			return (execve(cmd[0], cmd, NULL)); // Send consume(envp), Struct to Char**
		exit(-1);
	}
	path_var = find_path(envp);
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
			if (execve(*paths[0], cmd, NULL) == -1) // Send consume(envp), Struct to Char **
				return (-1);
		free(*paths[0]++);
	}
	return (free(paths[1]), -1);
}
