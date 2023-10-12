/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hacks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:06:48 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/12 14:14:44 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GET_EXIT 0xdeadbeef

int	exit_status_trolling(unsigned int action)
{
	static int	exit_status;

	if (action != GET_EXIT)
		exit_status = action;
	return (exit_status);
}

void	set_exit_status(unsigned int exit_status)
{
	exit_status_trolling(exit_status);
}

int	get_exit_status(void)
{
	return (exit_status_trolling(GET_EXIT));
}
