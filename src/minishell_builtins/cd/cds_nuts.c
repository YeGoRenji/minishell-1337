/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cds_nuts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:36:07 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/17 15:53:50 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_utils.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <executor.h>

int	change_directory(char *dir)
{
	char	*joined_paths;
	char	*trimmed_path;
	char	*path;
	int		status;

	if (!dir)
		return (1);
	if (chdir(dir) == -1)
	{
		perror("chdir");
		return (1);
	}
	path = structure_path(pwd_trolling(NULL), dir);
	if (!is_dir(path))
	{
		joined_paths = join_paths(pwd_trolling(NULL), dir);
		print_err(dir, -5);
		trimmed_path = trim_path(joined_paths);
		pwd_trolling(trimmed_path);
		(free(joined_paths), free(trimmed_path), free(path));
		status = 1;
	}
	else
		return (pwd_trolling(path), free(path), 0);
	return (status);
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
	char	*constructed;
	char	**dot_dot;

	if (!curr_dir || !dir)
		return (NULL);
	if (!ft_strcmp(dir, "."))
		return (ft_strdup(curr_dir));
	if (*dir == '/')
		return (ft_strdup(dir));
	if (!ft_strnstr(dir, "..", ft_strlen(dir)))
		return (join_paths(curr_dir, dir));
	dot_dot = handle_dot_dot_path(join_paths(curr_dir, dir));
	constructed = contruct_path(dot_dot);
	free_list(dot_dot);
	return (constructed);
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
