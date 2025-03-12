/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:40:37 by username          #+#    #+#             */
/*   Updated: 2024/12/06 23:44:37 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*buff;
	size_t	n;
	size_t	i;

	if (size && num > SIZE_MAX / size)
		return (NULL);
	n = num * size;
	buff = malloc(n);
	if (!buff)
		return (NULL);
	i = 0;
	while (i < n)
		((char *)buff)[i++] = 0;
	return (buff);
}

char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp_buffer;
	char	*eol;

	if (!*buffer)
		return (NULL);
	eol = ft_strchr(*buffer, '\n');
	if (eol)
	{
		line = ft_substr_ptr(*buffer, eol);
		temp_buffer = ft_strdup(eol + 1);
		free(*buffer);
		*buffer = temp_buffer;
		return (line);
	}
	return (NULL);
}

char	*handle_readed_chunck(char **buffer, int reads, char *temp_buffer)
{
	char	*line;
	char	*new_buffer;

	line = NULL;
	if (reads <= 0)
	{
		if (*buffer && **buffer && reads != -1)
			line = ft_strdup(*buffer);
		free(temp_buffer);
		free(*buffer);
		*buffer = NULL;
		return (line);
	}
	new_buffer = ft_strjoin(*buffer, temp_buffer);
	free(*buffer);
	free(temp_buffer);
	*buffer = new_buffer;
	return (NULL);
}

char	*read_more(int fd, char **buffer)
{
	char	*temp_buffer;
	int		reads;

	temp_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	reads = read(fd, temp_buffer, BUFFER_SIZE);
	return (handle_readed_chunck(buffer, reads, temp_buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (buffer)
	{
		line = extract_line(&buffer);
		if (line)
			return (line);
		temp_buffer = read_more(fd, &buffer);
		if (temp_buffer)
			return (temp_buffer);
	}
	return (NULL);
}
