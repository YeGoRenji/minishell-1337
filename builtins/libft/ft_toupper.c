/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:30:49 by afatimi           #+#    #+#             */
/*   Updated: 2022/10/08 12:18:28 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch >= 'a' && ch <= 'z')
		return (1);
	return (0);
}

int	ft_toupper(int c)
{
	unsigned char	ch;
	int				toggle;

	ch = (unsigned char)c;
	toggle = ft_islower(ch);
	return (c - 32 * toggle);
}
