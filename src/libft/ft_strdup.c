/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:43:16 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/14 01:18:46 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*target;

	len = ft_strlen(s1);
	target = malloc(len + 1);
	if (target)
	{
		ft_memcpy(target, s1, len);
		target[len] = '\0';
	}
	return (target);
}
