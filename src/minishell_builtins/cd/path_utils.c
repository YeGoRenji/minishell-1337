/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:00:21 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 13:04:33 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../global_utils.h"

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
		tmp = ft_strdup("/");
	}
	else
		tmp = ft_strjoin(dirname, "/");
	path = ft_strjoin(tmp, basename);
	return (free(tmp), path);
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
