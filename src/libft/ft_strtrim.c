/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:21:19 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/08/25 18:45:54 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_inset(char const *set, int c)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

static int	get_bounding(int dir, int index, char const *s1)
{
	if (dir == 1)
		return (index < (int)ft_strlen(s1));
	else
		return (index >= 0);
}

static int	ft_skipinset(char const *s1, char const *set, int dir)
{
	size_t	s1_len;
	int		index;

	s1_len = ft_strlen(s1);
	index = 0;
	if (dir == -1)
		index = s1_len - 1;
	while (get_bounding(dir, index, s1))
	{
		if (!ft_inset(set, s1[index]))
			break ;
		index += dir;
	}
	return (index);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start_index;
	int	end_index;

	if (!s1 || !set)
		return (NULL);
	if (!(*s1))
		return (ft_calloc(1, 1));
	start_index = ft_skipinset(s1, set, 1);
	end_index = ft_skipinset(s1, set, -1);
	return (ft_substr(s1, start_index, (end_index - start_index) + 1));
}
