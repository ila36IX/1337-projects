/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:44:02 by aljbari           #+#    #+#             */
/*   Updated: 2025/05/03 16:25:35 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

unsigned int	ft_atoi(char *s)
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
