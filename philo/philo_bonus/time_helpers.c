/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:51:49 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/18 02:51:49 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(time_t milliseconds, t_philo *philo)
{
	time_t	start;

	start = curr_time();
	while ((curr_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&philo->mtx_sim_status);
		if (!philo->sim_status)
		{
			pthread_mutex_unlock(&philo->mtx_sim_status);
			return ;
		}
		pthread_mutex_unlock(&philo->mtx_sim_status);
		usleep(500);
	}
}

time_t	time_since_dinner_starts(void)
{
	static time_t	dinner_start_clock;

	if (dinner_start_clock)
		return (curr_time() - dinner_start_clock);
	else
		dinner_start_clock = curr_time();
	return (curr_time() - dinner_start_clock);
}

void	start_dinner_clock(void)
{
	time_since_dinner_starts();
}

time_t	curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	log_action(char *action, t_philo *philo)
{
	sem_wait(philo->info.sem_write);
	pthread_mutex_lock(&philo->mtx_sim_status);
	if (philo->sim_status)
		printf(YELLOW "%ld" RESET " " BOLD "%d " RESET "%s\n",
			time_since_dinner_starts(), philo->id, action);
	pthread_mutex_unlock(&philo->mtx_sim_status);
	sem_post(philo->info.sem_write);
}
