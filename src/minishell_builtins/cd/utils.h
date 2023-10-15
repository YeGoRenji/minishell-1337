/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:17:57 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/14 22:36:21 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../global_utils.h"

void	change_directory(char *dir);
char	*structure_path(char *curr_dir, char *dir);
char	*join_paths(char *dirname, char *basename);
char	*join_dir_chunks(char *dirname, char *basename);
char	**handle_dot_dot_path(char *path);
int		doesnt_exist(char *path);
char	*consume_path(char *joined_paths);
void	shift_slices(char **slices);
int		has_dot_dot(char **slices);
#endif
