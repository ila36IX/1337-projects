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

	if (reads <= 0)
	{
		if (*buffer && **buffer)
		{
			line = ft_strdup(*buffer);
			free(*buffer);
			*buffer = NULL;
			free(temp_buffer);
			return (line);
		}
		free(temp_buffer);
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	temp_buffer[reads] = '\0';
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

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	reads = read(fd, temp_buffer, BUFFER_SIZE);
	return (handle_readed_chunck(buffer, reads, temp_buffer));
}

char	*read_file(int fd, char **buffer)
{
	char	*line;
	char	*temp_buffer;

	while (1)
	{
		line = extract_line(buffer);
		if (line)
			return (line);
		temp_buffer = read_more(fd, buffer);
		if (!temp_buffer && !buffer)
			return (NULL);
		if (!temp_buffer && !*buffer)
			return (NULL);
		if (temp_buffer)
			return (temp_buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer[fd])
			return (NULL);
		i = 0;
		while (i < (BUFFER_SIZE + 1))
			buffer[fd][i++] = '\0';
	}
	return (read_file(fd, &buffer[fd]));
}
