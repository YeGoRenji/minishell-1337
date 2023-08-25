/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 19:09:34 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/25 18:45:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src == dest)
		return (dest);
	if (src > dest)
		return (ft_memcpy(dest, src, n));
	while (n--)
		*(((char *)dest) + n) = *(((char *)src) + n);
	return (dest);
}
