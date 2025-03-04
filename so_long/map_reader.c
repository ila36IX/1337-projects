/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:58:36 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/04 00:58:44 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	del_nl(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		if (*s == '\n')
			*s = '\0';
		s++;
	}
}

char	**realloc_map(char **map, unsigned int size)
{
	unsigned int	i;
	char			**new_map;

	new_map = ft_calloc(size + 256, sizeof(char *));
	i = 0;
	while (i < size)
	{
		new_map[i] = map[i];
		i++;
	}
	free(map);
	return (new_map);
}

char	**read_map(char *path)
{
	char			**map;
	char			*line;
	unsigned int	i;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		sys_error_exit(path);
	map = ft_calloc(256, sizeof(char *));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		del_nl(line);
		map[i++] = line;
		line = get_next_line(fd);
		if (i % 254 == 0 && line)
			map = realloc_map(map, i);
	}
	if (close(fd) == -1)
		sys_error_exit(path);
	map_checker(map);
	return (map);
}
