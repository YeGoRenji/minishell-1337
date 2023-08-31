/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:50:09 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:45:19 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_byte_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}

static int	ft_word_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long long	*word_p1;
	unsigned long long	*word_p2;

	word_p1 = (unsigned long long *)s1;
	word_p2 = (unsigned long long *)s2;
	while (n--)
	{
		if (*word_p1 != *word_p2)
			return (ft_byte_memcmp(word_p1, word_p2, 8));
		word_p1++;
		word_p2++;
	}
	return (0);
}

static int	min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;
	size_t			tmp;

	if (((size_t)s1 & 7) != ((size_t)s2 & 7))
		return (ft_byte_memcmp(s1, s2, n));
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = min(n, (size_t)s1 & 7);
	tmp = ft_byte_memcmp(p1, p2, i);
	if (tmp)
		return (tmp);
	p1 += i;
	p2 += i;
	n -= i;
	tmp = ft_word_memcmp(p1, p2, n >> 3);
	if (tmp)
		return (tmp);
	p1 += n & ~7;
	p2 += n & ~7;
	return (ft_byte_memcmp(p1, p2, n & 7));
}
