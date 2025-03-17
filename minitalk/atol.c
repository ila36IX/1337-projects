/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:03:09 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/14 10:03:39 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

unsigned int	ft_atol_parse(char *s)
{
	unsigned long	n;

	n = 0;
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + *s++ - '0';
		if (n >= INT_MAX)
			return (INT_MAX);
	}
	if (*s)
		return (INT_MAX);
	return (n);
}
