/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <afatimi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:53:28 by afatimi           #+#    #+#             */
/*   Updated: 2023/10/10 16:40:32 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>
#include <unistd.h>

static char	*add_to_buff(char *buff, int fd)
{
	char	*chunk;
	char	*tmp;
	int		readed;

	chunk = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!chunk)
		return (NULL);
	readed = -1;
	while (!ft_strchr(chunk, '\n') && readed)
	{
		readed = read(fd, chunk, BUFFER_SIZE);
		if (!readed)
			break ;
		if (readed == -1)
			return (free(chunk), NULL);
		chunk[readed] = 0;
		tmp = ft_strjoin(buff, chunk);
		if (!tmp)
			return (free(buff), free(chunk), NULL);
		free(buff);
		buff = tmp;
	}
	return (free(chunk), buff);
}

static char	*get_line(char **buff)
{
	char	*line;
	char	*tmp;
	char	*end_of_line;
	size_t	line_len;

	if (!*buff)
		return (NULL);
	end_of_line = ft_strchr(*buff, '\n');
	if (!end_of_line)
	{
		if (!ft_strlen(*buff))
			return (NULL);
		tmp = ft_strdup(*buff);
		free(*buff);
		*buff = NULL;
		return (tmp);
	}
	line_len = end_of_line - *buff + 1;
	line = ft_substr(*buff, 0, line_len);
	if (!line)
		return (free(line), NULL);
	tmp = ft_strdup(*buff + line_len);
	free(*buff);
	*buff = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!buff)
		buff = ft_strdup("");
	buff = add_to_buff(buff, fd);
	line = get_line(&buff);
	if (!line)
	{
		free(buff);
		buff = NULL;
	}
	return (line);
}
