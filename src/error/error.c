/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 03:15:15 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/25 18:45:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>

void	tok_error(char which)
{
	write(2, "shell69: unexpected token `", 27);
	write(1, &which, 1);
	write(2, "'\n", 2);
}

void	unclosed_error(char which)
{
	write(2, "shell69: unclosed quote `", 25);
	write(1, &which, 1);
	write(2, "'\n", 2);
}

void	syntax_error(char *where)
{
	write(2, "shell69: syntax error near unexpected token `", 45);
	ft_putstr_fd(where, 2);
	write(2, "'\n", 2);
}
