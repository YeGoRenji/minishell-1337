/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:40:43 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/31 02:38:28 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h> // TODO : delete this
#include <stdlib.h>

t_env	*ft_lstnew(char *elem, t_env *prev)
{
	t_env	*node;
	size_t	split_index;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (!ft_strchr(elem, '='))
	{
		node -> key = ft_strdup(elem);
		node -> value = NULL;
		node -> equal_sign = NULL;
	}
	else
	{
		split_index = (size_t)ft_strchr(elem, '=') - (size_t)elem;
		node -> key = ft_substr(elem, 0, split_index);
		if (elem[split_index + 1] == '\0')
			node -> value = NULL;
		else
			node -> value = ft_strdup(elem + split_index + 1);
		node -> equal_sign = "";
	}
	node -> prev = prev;
	node -> next = NULL;
	return (node);
}
