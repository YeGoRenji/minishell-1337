/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:13:38 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/14 01:20:46 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (start >= s_len || (len == 0 && start == 0) || len == 0)
		return (ft_calloc(1, 1));
	if (s_len == 0)
		return (NULL);
	substr = malloc(min(s_len - start + 1, len + 1));
	if (!substr)
		return (NULL);
	while (s[start] && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
