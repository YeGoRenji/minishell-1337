/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:13:01 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/14 01:12:19 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	char			*p;
	unsigned char	uc;

	uc = (unsigned char) c;
	p = (char *)s;
	while (len--)
	{
		*p = uc;
		p++;
	}
	return (s);
}
