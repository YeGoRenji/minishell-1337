/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:53:01 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:43:48 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

unsigned long	char_to_long_long(char c)
{
	unsigned long long	res;

	res = (unsigned char)c \
		| ((unsigned char)c << 8) \
		| ((unsigned char)c << 16) \
		| (unsigned long)((unsigned char)c) << 24;
	return (res << 32 | res);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long long	*word_ptr;
	unsigned long long	word_byte;
	unsigned char		*ptr;
	unsigned int		align_len;
	unsigned int		i;

	if (!len)
		return (b);
	align_len = (size_t)b & 7;
	len -= align_len;
	ptr = (unsigned char *)b;
	while (align_len--)
		*ptr++ = (unsigned char)c;
	word_byte = char_to_long_long(c);
	word_ptr = (unsigned long long *)ptr;
	i = len >> 3;
	while (i--)
		*word_ptr++ = word_byte;
	ptr = (unsigned char *)word_ptr;
	len &= 7;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}
