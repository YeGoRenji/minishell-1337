/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:24:38 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 16:41:34 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo_utils.h"

static void	print_args(int argc, char **args, int i)
{
	while (i < argc - 1)
	{
		ft_putstr_fd(args[i++], 1);
		ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd(args[i++], 1);
}

int	echo(int argc, char **args)
{
	int		new_line;
	int		i;
	char	*opt;

	i = 0;
	new_line = 1;
	while (i <= argc - 1)
	{
		opt = args[i];
		if (opt && *opt && ft_strlen(opt + 1) && consist_of(opt + 1, 'n'))
		{
			new_line = 0;
			i++;
		}
		else
			break ;
	}
	print_args(argc, args, i);
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
