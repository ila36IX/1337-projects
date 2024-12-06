/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:35:30 by username          #+#    #+#             */
/*   Updated: 2024/12/06 23:29:42 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*src)
		str[i++] = *src++;
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*buff;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	buff = malloc(sizeof(char) * (i + j + 1));
	if (!buff)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[j])
			buff[i++] = s1[j++];
	j = 0;
	if (s2)
		while (s2[j])
			buff[i++] = s2[j++];
	buff[i] = '\0';
	return (buff);
}

char	*ft_substr_ptr(char const *start, char const *end)
{
	size_t	len;
	char	*str;
	size_t	i;

	if (!start || !end || end < start)
		return (NULL);
	len = end - start + 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = *start++;
	str[len] = '\0';
	return (str);
}
