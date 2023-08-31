/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:20:05 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:41:24 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	result = malloc(l1 + l2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, l1);
	ft_memcpy(result + l1, s2, l2);
	result[l1 + l2] = 0;
	return (result);
}
