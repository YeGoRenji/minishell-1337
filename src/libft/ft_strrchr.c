/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:26:42 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/25 18:45:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s) + 1;
	while (len--)
		if (s[len] == (unsigned char)c)
			return ((char *)(s + len));
	return (NULL);
}
