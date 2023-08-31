/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:31:45 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:41:01 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	src_len;
	unsigned int	dst_len;

	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	dst_len = ft_strlen(dest);
	if (size && dst_len < size)
	{
		ft_strncpy(&dest[dst_len], src, size - dst_len);
		return (src_len + dst_len);
	}
	else
		return (src_len + size);
}
