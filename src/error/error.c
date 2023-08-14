/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 03:15:15 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/14 03:21:16 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/error.h"

void	syntax_error(char *where)
{
	write(2, "shell69: syntax error near unexpected token `", 45);
	ft_putstr_fd(where, 2);
	write(2, "'\n", 2);
}
