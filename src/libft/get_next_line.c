/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 03:13:45 by ylyoussf          #+#    #+#             */
/*   Updated: 2022/11/18 13:50:38 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 69
#endif

static char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*target;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	s1_len = ft_strlen_noseg(s1);
	s2_len = ft_strlen_noseg(s2);
	target = malloc(s1_len + s2_len + 1);
	if (!target)
		return (NULL);
	ft_memcpy(target, s1, s1_len);
	ft_memcpy(target + s1_len, s2, s2_len);
	target[s1_len + s2_len] = '\0';
	return (free(s1), s1 = NULL, target);
}

static int	ft_read(char **big_buffer, int fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	bytes_read = -1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(*big_buffer), *big_buffer = NULL, 0);
		buffer[bytes_read] = '\0';
		*big_buffer = ft_strjoin_free(*big_buffer, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (1);
}

static char	*get_line(char *big_buffer)
{
	char	*new_line_pos;

	new_line_pos = ft_strchr(big_buffer, '\n');
	if (new_line_pos)
		return (ft_substr(big_buffer, 0, new_line_pos - big_buffer + 1));
	return (ft_strdup(big_buffer));
}

static char	*get_remainder(char *big_buffer)
{
	char	*new_line_pos;
	int		len;
	int		remainder_index;
	char	*tmp;

	new_line_pos = ft_strchr(big_buffer, '\n');
	len = ft_strlen_noseg(big_buffer);
	remainder_index = new_line_pos - big_buffer + 1;
	if (new_line_pos)
	{
		tmp = ft_substr(big_buffer, remainder_index, len - remainder_index);
		return (free(big_buffer), big_buffer = NULL, tmp);
	}
	free(big_buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*big_buffer;
	char		*actual_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (free(big_buffer), big_buffer = NULL, NULL);
	if (!ft_read(&big_buffer, fd))
		return (NULL);
	actual_line = get_line(big_buffer);
	big_buffer = get_remainder(big_buffer);
	if (*actual_line == '\0')
		return (free(actual_line), actual_line = NULL, NULL);
	return (actual_line);
}
