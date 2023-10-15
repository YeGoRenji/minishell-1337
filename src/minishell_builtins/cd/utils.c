/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:36:07 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/12 17:10:18 by afatimi          ###   ########.fr       */
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
		return ;
	}
	path = structure_path(pwd_trolling(NULL), dir);
	pwd_trolling(path);
	free(path);
}

char	*structure_path(char *curr_dir, char *dir)
{
	char	*path;
	char	**slice;
	char	**slice_ptr;
	char	*tmp;
	char	*tmp_path;

	if (!curr_dir || !dir)
		return (NULL);
	if (!ft_strcmp(dir, "."))
		return (ft_strdup(curr_dir));
	if (*dir == '/')
		return (ft_strdup(dir));
	if (!ft_strnstr(dir, "..", ft_strlen(dir)))
	{
		tmp = ft_strjoin(curr_dir, "/");
		path = ft_strjoin(tmp, dir);
		return (free(tmp), path);
	}
	path = ft_strdup("/");
	tmp_path = join_dirs(curr_dir, dir);
	slice = ft_split(tmp_path, '/');
	free(tmp_path);
	// TODO : protect this split?
	slice_ptr = slice;
	while (*slice_ptr)
	{
		//		printf("- slice = %s && slice++ = %s\n", *slice_ptr, *(slice_ptr + 1));
		if (*(slice_ptr + 1) && !ft_strcmp(*(slice_ptr + 1), ".."))
		{
			//			printf("skipping over '%s'\n", *slice_ptr);
			slice_ptr += 2;
			continue ;
		}
		//		printf("===> joining '%s' and '%s'\n", path, *slice_ptr);
		tmp = join_dirs(path, *slice_ptr);
		//		printf("===> so far path = '%s'\n", tmp);
		free(path);
		path = tmp;
		slice_ptr++;
	}
	free_list(slice);
	return (path);
}

char	*join_dirs(char *dirname, char *basename)
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
