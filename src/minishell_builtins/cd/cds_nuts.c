/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cds_nuts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:36:07 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 17:58:17 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_utils.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	change_directory(char *dir)
{
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
	if (!opendir(path))
	{
		ft_putendl_fd("shell69: cd: ..: No such file or directory", 2);
		pwd_trolling(trim_path(join_paths(pwd_trolling(NULL), dir)));
		status = 1;
	}
	else
	{
		pwd_trolling(structure_path(pwd_trolling(NULL), dir));
		status = 0;
	}
	free(path);
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
