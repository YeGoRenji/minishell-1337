/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:39:47 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:39:43 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	ch;

	ptr = (char *)s + ft_strlen(s);
	ch = (unsigned char)c;
	while (ptr >= s)
	{
		if (*ptr == ch)
			return (ptr);
		ptr--;
	}
	return (0);
}
