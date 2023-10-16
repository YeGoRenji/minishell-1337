/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:09:12 by ylyoussf          #+#    #+#             */
/*   Updated: 2022/11/16 18:44:34 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

size_t	ft_strlen_noseg(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}
