/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:08:10 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/08 10:05:14 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_isspace(char c)
{
	char	*spaces;
	int		found;

	found = 0;
	spaces = " \f\n\r\t\v";
	while (*spaces)
	{
		if (*spaces++ == c)
			found = 1;
	}
	return (found);
}

static long	nbr_overflow(int sign, unsigned long nbr)
{
	if ((sign > 0 && nbr > INT_MAX) || (sign < 0 && (long)(nbr * -1) < INT_MIN))
		return (1);
	return (0);
}

/**
 * ft_atol - convert string into long
 *
 * @str: string
 * Return: long
 */
long	ft_atol(const char *str)
{
	char			c;
	int				sign;
	unsigned long	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		c = *str++;
		nbr *= 10;
		nbr += (c - '0');
		if (nbr_overflow(sign, nbr))
			return (nbr * sign);
	}
	return (nbr * sign);
}
