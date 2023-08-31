/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:19:25 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:47:13 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (!lst || !new)
		return ;
	ptr = *lst;
	if (ptr)
		ft_lstlast(ptr)->next = new;
	else
		*lst = new;
}
