/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:03:32 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/15 16:07:16 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_malloc(unsigned long size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		print_err("malloc", -2);
		exit(get_exit_status());
	}
	return (ptr);
}
