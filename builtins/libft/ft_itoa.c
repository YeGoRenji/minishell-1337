/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:24 by afatimi           #+#    #+#             */
/*   Updated: 2023/08/30 22:47:05 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_get_ten_pow(int nbr)
{
	int	base;
	int	devide;

	devide = 10;
	if (nbr < 0)
		devide = -10;
	base = 0;
	while (nbr != 0)
	{
		nbr = nbr / devide;
		base++;
		if (devide < 10)
			devide = devide * -1;
	}
	return (base - 1);
}

static int	ft_ten_pow(int power, int sign)
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

void	ft_fill_buffer(long n, int power, char *result)
{
	unsigned int	i;
	int				sign;

	i = 0;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		result[i++] = '-';
	}
	while (power >= 0)
	{
		result[i++] = '0' + n / ft_ten_pow(power, sign);
		n %= ft_ten_pow(power, sign);
		power = power - 1;
	}
	result[i] = 0;
}

char	*ft_itoa(int nbr)
{
	long	n;
	char	*result;
	int		power;

	if (!nbr)
		return (ft_strdup("0"));
	n = (long)nbr;
	power = ft_get_ten_pow(n);
	result = (char *)malloc(((power + 2 + (n < 0))) * sizeof(char));
	if (!result)
		return (NULL);
	ft_fill_buffer(n, power, result);
	return (result);
}
