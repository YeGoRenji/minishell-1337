/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:40:43 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/13 17:00:41 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "global_utils.h"
#include "lst_operations.h"
#include <libft.h>
#include <stdio.h> // TODO : delete this
#include <stdlib.h>

t_env	*ft_lstnew(char *key, char *value, int equal_sign, t_env *prev)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->prev = prev;
	node->next = NULL;
	node->equal_sign = equal_sign;
	return (node);
}

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

void	ft_lstdelone(t_env *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->key);
	del(lst->value);
	lst->key = NULL;
	lst->value = NULL;
	lst->prev = NULL;
	lst->next = NULL;
	free(lst);
}

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

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
