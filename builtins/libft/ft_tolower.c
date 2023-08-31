/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:30:49 by afatimi           #+#    #+#             */
/*   Updated: 2022/11/05 18:44:07 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isupper(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch >= 'A' && ch <= 'Z')
		return (1);
	return (0);
}

int	ft_tolower(int c)
{
	unsigned char	ch;
	int				toggle;

	ch = (unsigned char)c;
	toggle = ft_isupper(ch);
	return (c | 32 * toggle);
}
