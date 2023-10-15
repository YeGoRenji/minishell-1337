/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:35:51 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/12 14:26:52 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

void	my_exit(char *arg)
{
	int	status;

	status = get_exit_status();
	if (arg)
		status = ft_atoi(arg);
	free(pwd_trolling(NULL));
	exit(status);
}
