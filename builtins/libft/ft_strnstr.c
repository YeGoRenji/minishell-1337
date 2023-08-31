/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:22:02 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:39:50 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *to, size_t n)
{
	size_t	j;
	size_t	i;
	char	*haystack;
	char	*needle;

	i = 0;
	haystack = (char *)s;
	needle = (char *)to;
	if ((!needle || !haystack) && n == 0)
		return (NULL);
	if (needle[i] == '\0')
		return (haystack);
	while (haystack[i] != '\0' && i < n)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j] && i + j < n)
			j++;
		if (needle[j] == '\0')
			return (haystack + i);
		i++;
	}
	return (0);
}
