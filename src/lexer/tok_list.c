/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 02:56:22 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/11 03:05:26 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

t_token	*ft_toklast(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ft_toklast(*lst)->next = new;
}

void	ft_tokiter(t_token *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}
