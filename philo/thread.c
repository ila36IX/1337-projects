/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:30:59 by aljbari           #+#    #+#             */
/*   Updated: 2025/05/03 16:20:11 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	init_forks(pthread_mutex_t *forks, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
		pthread_mutex_init(forks + i++, NULL);
}

void	run_threads(t_philo *philos, pthread_t *threads)
{
	int	i;

	start_dinner_clock();
	i = 0;
	while (i < philos[0].num_of_philos)
	{
		philos[i].last_meal_time = curr_time();
		pthread_create(&threads[i], NULL, thread_func, &philos[i]);
		i += 2;
	}
	usleep(500);
	i = 1;
	while (i < philos[0].num_of_philos)
	{
		philos[i].last_meal_time = curr_time();
		pthread_create(&threads[i], NULL, thread_func, &philos[i]);
		i += 2;
	}
}

void	philo_life(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		log_action("has taken a fork", philo);
		ft_usleep(philo->ttd + 50, philo);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	log_action("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->eat_mtx);
	philo->last_meal_time = curr_time();
	philo->eat_times++;
	pthread_mutex_unlock(&philo->eat_mtx);
	log_action("has taken a fork", philo);
	log_action("is eating", philo);
	ft_usleep(philo->tte, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	log_action("is sleeping", philo);
	ft_usleep(philo->tts, philo);
	log_action("is thinking", philo);
}

void	*thread_func(void *p)
{
	t_philo	*philo;

	philo = p;
	while (1)
	{
		pthread_mutex_lock(&philo->eat_mtx);
		if (!philo->dinner_status)
		{
			pthread_mutex_unlock(&philo->eat_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->eat_mtx);
		philo_life(philo);
	}
	return (NULL);
}
