/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:51:40 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/15 16:18:05 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*target;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	target = ft_malloc(count * size);
	if (target)
		ft_bzero(target, count * size);
	return (target);
}
