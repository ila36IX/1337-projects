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
#include <stdio.h>

char	*ft_nl_strdup(const char *src)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2)); 
	if (!str)
		return (NULL);
	j = 0;
	while (j <= i) 
	{
		str[j] = src[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char *string;
	char *line, *temp;
	int read_size;
	char *nl_location;

	if (cache)
	{
		// printf("cache [%s]\n", cache);
		nl_location = ft_strchr(cache, '\n');
		if (nl_location)
		{
			line = ft_nl_strdup(cache);
			free(cache);
			cache = ft_strdup(nl_location + 1);
			return (line);
		}
		else
		{
			string = malloc(BUFFER_SIZE + 1);
			while (ft_strchr(cache, '\n') == NULL)
			{
				read_size = read(fd, string, BUFFER_SIZE);
				string[read_size] = 0;
				temp = cache;
				cache = ft_strjoin(cache, string);
				free(temp);
				if (read_size == 0)
				{
					line = ft_strdup(cache);
					free(cache);
					cache = NULL;
					free(string);
					return (line);
				}                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
			}
			free(string);
			nl_location = ft_strchr(cache, '\n');
			line = ft_nl_strdup(cache);
			temp = cache;
			cache = ft_strdup(nl_location + 1);
			free(temp);
			return (line);
		}
	}

	string = malloc(BUFFER_SIZE + 1);
	read_size = read(fd, string, BUFFER_SIZE);
	if (read_size == 0)
	{
		free(string);
		return (NULL);
	}
	string[read_size] = 0;

	nl_location = ft_strchr(string, '\n');
	if (nl_location) 
	{
		cache = ft_strdup(nl_location + 1);
		line = ft_nl_strdup(string);
	}
	free(string);
	return (line);
}
