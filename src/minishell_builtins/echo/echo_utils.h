/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:24:38 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 16:38:02 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_UTILS_H
# define ECHO_UTILS_H
# include "../global_utils.h"
# include <unistd.h>

void	print_spaced_arg(char *arg);
void	print_last_arg(char *arg, int new_line);
int		consist_of(char *line, char c);
size_t	count(const char *s, int c);
#endif
