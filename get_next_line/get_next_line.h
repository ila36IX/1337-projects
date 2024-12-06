/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:29:15 by aljbari           #+#    #+#             */
/*   Updated: 2024/12/06 22:38:49 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_substr_ptr(char const *start, char const *end);
char	*ft_strdup(const char *src);
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif
#endif
