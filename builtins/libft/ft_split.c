/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:14:49 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:41:48 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	count_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

size_t	ft_custom_strlen(const char *s, int c)
{
	unsigned int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

void	*free_list(char **list)
{
	unsigned int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*ptr;
	size_t	words_count;
	size_t	i;
	size_t	word_len;

	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	result = (char **)ft_calloc((words_count + 1), sizeof(char *));
	if (!result)
		return (NULL);
	ptr = (char *)s;
	i = 0;
	while (i < words_count)
	{
		while (*ptr == c)
			ptr++;
		word_len = ft_custom_strlen(ptr, c);
		result[i++] = ft_substr(ptr, 0, word_len);
		if (!result[i - 1])
			return (free_list(result));
		ptr += word_len + 1;
	}
	return (result);
}
