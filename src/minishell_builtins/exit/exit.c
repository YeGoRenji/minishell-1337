/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:35:51 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/15 15:41:04 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_utils.h"
#include <stdlib.h>

static int	handle_int(char *str_number, int len)
{
	char	*max_min_str;

	max_min_str = "9223372036854775807";
	if (*str_number == '-' || *str_number == '+')
		if (*str_number++ == '-')
			max_min_str = "9223372036854775808";
	if (len > 19 || ft_memcmp(str_number, max_min_str, len) > 0)
		return (0);
	return (1);
}

static int	check_arg(char *arg)
{
	int		len;
	char	*tmp;
	int		still_zero;

	len = 0;
	tmp = arg;
	still_zero = 1;
	if (!arg || *arg == '\0')
		return (0);
	if (*arg == '+' || *arg == '-')
		arg++;
	if (*arg == '\0')
		return (0);
	while (*arg)
	{
		if (!ft_isdigit(*arg++))
			return (0);
		if (*arg != '0')
			still_zero = 0;
		len += !still_zero;
	}
	if (len >= 19)
		return (handle_int(tmp, len));
	return (1);
}

void	my_exit(char *arg)
{
	if (arg && !check_arg(arg))
		print_err(arg, -6);
	else if (arg)
		set_exit_status(ft_atoi(arg));
	exit(get_exit_status());
}
