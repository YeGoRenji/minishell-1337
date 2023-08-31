/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:53:39 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:41:08 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	min(size_t n, size_t m)
{
	return (n * (n <= m) + m * (n > m));
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	size_to_copy;

	if (!size)
		return (ft_strlen(src));
	size_to_copy = min(size - 1, ft_strlen(src));
	ft_memcpy(dest, src, size_to_copy);
	dest[size_to_copy] = 0;
	return (ft_strlen(src));
}
