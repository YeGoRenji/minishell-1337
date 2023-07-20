/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:32:00 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/07/20 00:40:05 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

bool parser(t_list *tokens)
{
	printf("Hello from parser %s\n", ((t_token *)tokens->content)->value);
	return (true);
}
