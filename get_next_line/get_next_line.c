/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:40:37 by username          #+#    #+#             */
/*   Updated: 2024/12/04 17:57:20 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strchr(const char *s, int c)
{
  while (*s)
  {
    if (*s == (char)c)
      return ((char *)s);
    s++;
  }
  if ((char)c == 0)
    return ((char *)s);
  return (NULL);
}

#include <stdio.h>

char *extract_line(char **buffer)
{
  char *line;
  char *temp_buffer;
  char *eol;

  eol = ft_strchr(*buffer, '\n');
  if (eol)
  {
    // Extract line up to newline
    line = ft_substr_ptr(*buffer, eol);

    // Move buffer past newline
    temp_buffer = ft_strdup(eol + 1);
    free(*buffer);
    *buffer = temp_buffer;
    return (line);
  }
  return (NULL);
}

char *read_more(int fd, char **buffer)
{
  char *temp_buffer;
  char *new_buffer;
  char *line;
  int reads;
  // If no newline, prepare for reading more
  temp_buffer = malloc(BUFFER_SIZE + 1);
  if (!temp_buffer)
  {
    free(*buffer);
    *buffer = NULL;
    return (NULL);
  }

  // Read from file
  reads = read(fd, temp_buffer, BUFFER_SIZE);

  // Handle read errors or end of file
  if (reads <= 0)
  {
    // Return last buffer content if not empty
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

  // Null-terminate the read buffer
  temp_buffer[reads] = '\0';

  // Combine existing buffer with new read
  new_buffer = ft_strjoin(*buffer, temp_buffer);
  free(*buffer);
  free(temp_buffer);
  *buffer = new_buffer;
  return (NULL);
}


char *get_next_line(int fd)
{
  static char *buffer;
  char *line;
  char *temp_buffer;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
  if (!buffer)
  {
    buffer = calloc(1, BUFFER_SIZE + 1);
    if (!buffer)
      return (NULL);
  }
  while(1)
  {
    line = extract_line(&buffer);
    if (line)
      return (line);
    temp_buffer = read_more(fd, &buffer);
    if (!temp_buffer && !buffer)
      return (NULL);
    if (temp_buffer)
      return (temp_buffer);
  }
}

