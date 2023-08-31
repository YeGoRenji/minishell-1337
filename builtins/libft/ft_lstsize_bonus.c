/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:48:46 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:48:37 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_env *lst)
{
	t_env	*ptr;
	size_t	count;

	ptr = lst;
	if (!ptr)
		return (0);
	count = 1;
	while (ptr->next)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}
