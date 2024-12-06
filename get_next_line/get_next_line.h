/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:29:15 by aljbari           #+#    #+#             */
/*   Updated: 2024/12/03 19:35:17 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>


typedef struct t_buffer {
	char *s;
	int last_read_i;
	int size;
} t_buffer;
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *s);
char *get_next_line(int fd);
char *ft_substr_ptr(char const *start, char const *end);
char	*ft_strdup(const char *src);
# ifndef BUFFER_SIZE
#   define BUFFER_SIZE 69
# endif

