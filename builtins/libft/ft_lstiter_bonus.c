/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:20:29 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:47:50 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	if (!lst || !f)
		return ;
	ptr = lst;
	while (ptr)
	{
		tmp = ptr->next;
		f(ptr->content);
		ptr = tmp;
	}
}
