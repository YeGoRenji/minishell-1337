/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hacks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:06:42 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/26 21:36:00 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HACKS_H
# define HACKS_H
# include <libft.h>

enum
{
	ATTR_SET,
	ATTR_GET,
	ATTR_CHG
};

void	set_exit_status(unsigned int exit_status);
int		get_exit_status(void);
char	*make_dangling(unsigned long long dick_len);
#endif
