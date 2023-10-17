/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 03:15:15 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/10/17 16:04:15 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>

void	tok_error(char which)
{
	set_exit_status(258);
	write(2, "shell69: unexpected token `", 27);
	write(2, &which, 1);
	write(2, "'\n", 2);
}

void	unclosed_error(char which)
{
	set_exit_status(258);
	write(2, "shell69: unclosed quote `", 25);
	write(2, &which, 1);
	write(2, "'\n", 2);
}

void	syntax_error(char *where)
{
	set_exit_status(258);
	write(2, "shell69: syntax error near unexpected token `", 45);
	ft_putstr_fd(where, 2);
	write(2, "'\n", 2);
}

/*
	- msg_code == 0 => use perror instead
	- msg_code == 255 => command not found
	- msg_code == -69 => Is a directory
	- msg_code == -2 => allocation error
	- msg_code == -3 => $PATH var unset
	- msg_code == -4 => ambiguous redirect
	- msg_code == -5 => No such file or directory
	- msg_code == -6 => numeric argument required
*/
int	print_err(char *preced, int msg_code)
{
	t_strbuilder	*sb;

	sb = stringbuilder();
	sb_append(sb_append(sb, "shell69: "), preced);
	if (msg_code == -1)
		(sb_append(sb, ": command not found\n"), set_exit_status(127));
	else if (msg_code == -69)
		(sb_append(sb, ": Is a directory\n"), set_exit_status(126));
	else if (msg_code == -2)
		(sb_append(sb, ": allocation error\n"), set_exit_status(255));
	else if (msg_code == -3)
		(sb_append(sb, ": $PATH var unset\n"), set_exit_status(127));
	else if (msg_code == -4)
		(sb_append(sb, ": ambiguous redirect\n"), set_exit_status(1));
	else if (msg_code == -5)
		(sb_append(sb, ": No such file or directory\n"), set_exit_status(1));
	else if (msg_code == -6)
		(sb_append(sb, ": numeric argument required\n"), set_exit_status(255));
	if (msg_code == 0)
		perror(sb->str);
	else
		ft_putstr_fd(sb->str, 2);
	sb_free(sb);
	return (msg_code);
}
