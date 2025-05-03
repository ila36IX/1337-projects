/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:46:04 by aljbari           #+#    #+#             */
/*   Updated: 2025/05/03 15:46:16 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner_clock(void)
{
	time_since_dinner_starts();
}

t_microsec	curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
#define CHUNK_TIME 10

void	wait_in_mili(t_microsec amount)
{
	usleep(amount * 1000);
}

t_microsec	time_since_dinner_starts(void)
{
	static time_t	dinner_start_clock;

	if (dinner_start_clock)
		return (curr_time() - dinner_start_clock);
	else
		dinner_start_clock = curr_time();
	return (curr_time() - dinner_start_clock);
}
