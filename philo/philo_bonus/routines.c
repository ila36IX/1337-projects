/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:53:05 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/18 02:53:05 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*sim_status_func(void *_philo)
{
	t_philo	*philo;

	philo = _philo;
	sem_wait(philo->info.sem_sim_status);
	pthread_mutex_lock(&philo->mtx_sim_status);
	philo->sim_status = 0;
	pthread_mutex_unlock(&philo->mtx_sim_status);
	return (NULL);
}

/**
 * am_alive - thread function that keeps checking if philosopher last eat time
 * does cause death
 *
 * @_philo: philo infos
 * Return: Nothing, the function will keep checking until it got stopped by
 * SIGTERM signal, or if it exits
 */
void	*am_alive(void *_philo)
{
	t_philo	*philo;

	philo = _philo;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx);
		if (curr_time() - philo->last_eat_time > philo->info.ttd)
		{
			pthread_mutex_unlock(&philo->mtx);
			sem_wait(philo->info.sem_write);
			pthread_mutex_lock(&philo->mtx_sim_status);
			if (philo->sim_status)
				printf("%ld %d is dead\n", time_since_dinner_starts(),
					philo->id);
			philo->sim_status = 0;
			pthread_mutex_unlock(&philo->mtx_sim_status);
			unlock_semaphores(philo);
			usleep(5000);
			sem_post(philo->info.sem_write);
			return (0);
		}
		pthread_mutex_unlock(&philo->mtx);
		usleep(500);
	}
}

void	*check_full(void *_philos)
{
	int		i;
	t_philo	*philos;

	philos = _philos;
	i = philos->info.nbr;
	while (i > 0)
	{
		sem_wait(philos->info.sem_full);
		i--;
	}
	unlock_semaphores(philos);
	return (NULL);
}
