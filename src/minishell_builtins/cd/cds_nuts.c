/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:36:07 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/14 22:42:25 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // TODO : GET RID OF THIS AND USE LIBFT's INSTEAD!!
#include <unistd.h>

void	change_directory(char *dir)
{
	char	*path;

	if (!dir)
		return ;
	if (chdir(dir) == -1)
	{
		perror("chdir");
		set_exit_status(1);
		return ;
	}
	path = structure_path(pwd_trolling(NULL), dir);
	if (!opendir(path))
	{
		fprintf(stderr, "SHELL69: cd: ..: No such file or directory\n");
		pwd_trolling(trim_path(join_paths(pwd_trolling(NULL), dir)));
	}
	else
		pwd_trolling(structure_path(pwd_trolling(NULL), dir));
	free(path);
}

char	*contruct_path(char **path)
{
	t_strbuilder	*sb;
	char			*consumed;

	if (!*path)
		return (ft_strdup("/"));
	sb = stringbuilder();
	while (*path)
	{
		sb_append(sb, "/");
		sb_append(sb, *path);
		path++;
	}
	consumed = sb->str;
	free(sb);
	return (consumed);
}

char	*structure_path(char *curr_dir, char *dir)
{
	if (!curr_dir || !dir)
		return (NULL);
	if (!ft_strcmp(dir, "."))
		return (ft_strdup(curr_dir));
	if (*dir == '/')
		return (ft_strdup(dir));
	if (!ft_strnstr(dir, "..", ft_strlen(dir)))
		return (join_paths(curr_dir, dir));
	return (contruct_path(handle_dot_dot_path(join_paths(curr_dir, dir))));
}

int	is_dot_dot(char *slice)
{
	if (!slice)
		return (false);
	return (!ft_strcmp(slice, ".."));
}

void	trim_slices(char **slices)
{
	if (!slices || !*slices)
		return ;
	while (*slices && is_dot_dot(*slices))
	{
		free(*slices);
		*slices = NULL;
		slices++;
	}
	while (*slices && !is_dot_dot(*slices))
		slices++;
	if (*slices)
		shift_slices(slices - 1);
}

char	**handle_dot_dot_path(char *joined_paths)
{
	char	**slices;

	if (!joined_paths)
		return (NULL);
	slices = ft_split(joined_paths, '/');
	free(joined_paths);
	while (slices && has_dot_dot(slices))
		trim_slices(slices);
	return (slices);
}

int	has_dot_dot(char **slices)
{
	size_t	i;

	if (!slices || !*slices)
		return (false);
	i = 0;
	while (slices[i])
	{
		if (!ft_strcmp(slices[i++], ".."))
			return (true);
	}
	return (false);
}

void	shift_slices(char **slices)
{
	if (!slices && !*slices)
		return ;
	free(slices[0]);
	free(slices[1]);
	slices[0] = NULL;
	slices[1] = NULL;
	while (slices[2])
	{
		slices[0] = slices[2];
		slices++;
	}
	slices[0] = slices[2];
}

int	doesnt_exist(char *path)
{
	DIR		*useless_dir;
	char	*tmp_trim;
	int		res;

	if (!path)
		return (-1);
	tmp_trim = trim_path(path);
	useless_dir = opendir(tmp_trim);
	res = !!useless_dir;
	if (useless_dir)
	{
		res = 0;
		closedir(useless_dir);
	}
	else
		res = -1;
	return (res);
}

char	*join_paths(char *dirname, char *basename)
{
	char	*path;
	char	*tmp;

	if (!dirname || !basename)
		return (NULL);
	tmp = ft_strjoin(dirname, "/");
	path = ft_strjoin(tmp, basename);
	return (free(tmp), path);
}

char	*join_dir_chunks(char *dirname, char *basename)
{
	char	*tmp;
	char	*path;

	if (!dirname || !basename)
		return (NULL);
	if (!ft_strcmp(dirname, "/"))
	{
		if (!ft_strcmp(basename, ".."))
			return (ft_strdup("/"));
		tmp = strdup("/");
	}
	else
		tmp = ft_strjoin(dirname, "/");
	path = ft_strjoin(tmp, basename);
	return (free(tmp), path);
}
