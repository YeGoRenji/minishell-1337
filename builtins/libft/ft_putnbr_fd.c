/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:50:51 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:42:04 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_get_ten_pow(int nbr)
{
	int	base;
	int	devide;

	devide = 10;
	if (nbr < 0)
	{
		devide = -10;
	}
	base = 0;
	while (nbr != 0)
	{
		nbr = nbr / devide;
		base++;
		if (devide < 10)
		{
			devide = devide * -1;
		}
	}
	return (base - 1);
}

int	ft_ten_pow(int power, int sign)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	if (!power && sign == 1)
		return (1);
	while (i < power)
	{
		result = result * 10;
		i++;
	}
	return (result * sign);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		power;
	int		sign;
	char	c;

	sign = 1;
	if (!n)
		ft_putchar_fd('0', fd);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -1;
	}
	power = ft_get_ten_pow(n);
	while (power >= 0)
	{
		c = '0' + n / ft_ten_pow(power, sign);
		n %= ft_ten_pow(power, sign);
		ft_putchar_fd(c, fd);
		power = power - 1;
	}
}
