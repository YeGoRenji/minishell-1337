/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:21:58 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:43:59 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	unsigned int	diff;

	if (!dest && !src)
		return (NULL);
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	diff = (size_t)d - (size_t)s;
	if (!(d >= s && diff <= ft_strlen((void *)d)))
		return (ft_memcpy(d, s, n));
	while (n--)
		d[n] = s[n];
	return (dest);
}
