/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:50:50 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/25 18:45:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*target;
	int		i;

	if (!s || !f)
		return (NULL);
	target = ft_strdup(s);
	if (!target)
		return (NULL);
	i = 0;
	while (target[i])
	{
		target[i] = f(i, target[i]);
		i++;
	}
	return (target);
}
