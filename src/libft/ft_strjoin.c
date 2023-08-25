/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:57:28 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/25 18:45:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*target;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	target = malloc(s1_len + s2_len + 1);
	if (!target)
		return (NULL);
	ft_memcpy(target, s1, s1_len);
	ft_memcpy(target + s1_len, s2, s2_len);
	target[s1_len + s2_len] = '\0';
	return (target);
}
