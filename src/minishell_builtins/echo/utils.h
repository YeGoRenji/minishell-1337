/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:24:38 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/11 14:22:03 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../global_utils.h"
# include <unistd.h>

void	print_spaced_arg(char *arg);
void	print_last_arg(char *arg, int new_line);
int		consist_of(char *line, char c);
size_t	count(const char *s, int c);
#endif
