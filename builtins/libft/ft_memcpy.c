/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:29:20 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:44:07 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_fast_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long long	*word_src;
	unsigned long long	*word_dst;
	unsigned char		*byte_src;
	unsigned char		*byte_dst;
	size_t				i;

	word_src = (unsigned long long *)src;
	word_dst = (unsigned long long *)dst;
	i = n >> 3;
	while (i)
	{
		*word_dst++ = *word_src++;
		i--;
	}
	n -= i << 3;
	i = n & 7;
	byte_src = (unsigned char *)word_src;
	byte_dst = (unsigned char *)word_dst;
	while (i--)
		*byte_dst++ = *byte_src++;
	return (dst);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	if (!((size_t)dst & 7) && !((size_t)src & 7))
		return (ft_fast_memcpy(dst, src, n));
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
