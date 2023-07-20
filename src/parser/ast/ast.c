/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:25 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/20 00:42:37 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_node	*new_node(t_node_type type, t_node *left, t_node *right)
{
	t_node *new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->left = left;
	new->right = right;
	new->type = type;
	return (new);
}
