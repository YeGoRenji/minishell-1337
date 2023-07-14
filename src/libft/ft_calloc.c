/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:51:40 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/14 01:11:04 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*target;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	target = malloc(count * size);
	if (target)
		ft_bzero(target, count * size);
	return (target);
}
