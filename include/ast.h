/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/17 18:42:11 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum s_node_type
{
	AND,
	OR,
	PIPE,
	COMMAND
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char 			*output;
	char 			*input;
	struct s_node 	*right;
	struct s_node 	*left;
} t_node;

#endif // AST_H
