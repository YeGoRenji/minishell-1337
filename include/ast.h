/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/20 00:39:47 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "libft.h"

typedef enum e_node_type
{
	P_AND,
	P_OR,
	P_PIPE,
	P_COMMAND
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char 			*output;
	char 			*input;
	struct s_node 	*right;
	struct s_node 	*left;
} t_node;

t_node	*new_node(t_node_type type, t_node *left, t_node *right);

#endif // AST_H
