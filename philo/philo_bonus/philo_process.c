/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:23:28 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/18 02:51:59 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_simulation(t_philo *philos)
{
	int	i;

	start_dinner_clock();
	i = 0;
	while (i < philos->info.nbr)
	{
		start_philo_process(&philos[i]);
		i++;
	}
}

bool	philo_try_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_sim_status);
	if (!philo->sim_status)
	{
		pthread_mutex_unlock(&philo->mtx_sim_status);
		return (false);
	}
	pthread_mutex_unlock(&philo->mtx_sim_status);
	sem_wait(philo->info.sem_forks);
	log_action("has taken a fork", philo);
	sem_wait(philo->info.sem_forks);
	pthread_mutex_lock(&philo->mtx);
	philo->last_eat_time = curr_time();
	philo->eat_times++;
	if (philo->eat_times == philo->info.time_of_eats)
		sem_post(philo->info.sem_full);
	pthread_mutex_unlock(&philo->mtx);
	log_action("has taken a fork!", philo);
	return (true);
}

/**
 * philo_life - the miserable life of a philospher
 * take fork - eat - sleep - think - repeat waiting for its death
 */
void	philo_life(t_philo *philo)
{
	if (philo->id % 2)
		usleep(500);
	while (1)
	{
		if (!philo_try_take_forks(philo))
			return ;
		log_action("is eating", philo);
		ft_usleep(philo->info.tte, philo);
		sem_post(philo->info.sem_forks);
		sem_post(philo->info.sem_forks);
		log_action("is sleeping", philo);
		ft_usleep(philo->info.tts, philo);
		log_action("is thinking", philo);
		if (philo->info.nbr % 2)
			usleep(500);
	}
}

void	start_philo_process(t_philo *philo)
{
	pid_t		pid;
	pthread_t	monitor;
	pthread_t	sim_status;

	philo->last_eat_time = curr_time();
	pid = fork();
	philo->pid = pid;
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		pthread_create(&monitor, NULL, am_alive, philo);
		pthread_create(&sim_status, NULL, sim_status_func, philo);
		philo_life(philo);
		pthread_join(monitor, NULL);
		pthread_join(sim_status, NULL);
		process_release_resources(philo);
		exit(0);
	}
}
