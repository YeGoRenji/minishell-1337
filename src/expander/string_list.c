/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:56:55 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/11 17:01:55 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>
#include <assert.h>

t_str	*new_str(char *str, bool to_expand)
{
	t_str	*node;

	node = malloc(sizeof(t_str));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->wild_card = to_expand;
	node->next = NULL;
	return (node);
}

t_str	*ft_strlast(t_str *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	free_strnode(t_str *node)
{
	free(node->str);
	free(node);
}

int	ft_strlstlen(t_str *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	ft_striter(t_str *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}
