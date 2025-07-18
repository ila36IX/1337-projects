/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:46:12 by aljbari           #+#    #+#             */
/*   Updated: 2025/05/03 15:47:00 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dinner_as_over(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philos[0].status_mtx);
	while (i < philos[0].num_of_philos)
		philos[i++].dinner_status = 0;
	pthread_mutex_unlock(philos[0].status_mtx);
}

void	log_action(char *action, t_philo *philo)
{
	pthread_mutex_lock(philo->status_mtx);
	if (philo->dinner_status == 0)
	{
		pthread_mutex_unlock(philo->status_mtx);
		return ;
	}
	printf(YELLOW "%ld" RESET " " BOLD "%d " RESET "%s\n",
		time_since_dinner_starts(), philo->number, action);
	pthread_mutex_unlock(philo->status_mtx);
}

/**
 * check_philos_full - check if all philosophers eats at least
 * number_of_times_each_philosopher_must_eat times, if true the dinner status
 * of all philosophers will set to 0
 *
 * @philos: list of all philosophers, at least one should exist
 *
 * Return: Nothing
 */
void	check_philos_full(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(&philos[i].eat_mtx);
		if (philos[i].eat_times < philos[i].must_eat_times)
		{
			pthread_mutex_unlock(&philos[i].eat_mtx);
			return ;
		}
		pthread_mutex_unlock(&philos[i].eat_mtx);
		i++;
	}
	set_dinner_as_over(philos);
	return ;
}

/**
 * starvation_not_found - Check if all philosophers is alive, if a dead
 * one found the dinner status of all philosophers will be set to 0
 *
 * @philos: list of all philosophers, at least one should exist
 *
 * Return: Nothing
 */
void	check_starvation(t_philo *philos)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		philo = &philos[i];
		pthread_mutex_lock(&philo->eat_mtx);
		if (curr_time() - philo->last_meal_time > philo->ttd)
		{
			set_dinner_as_over(philos);
			printf(RED "%ld %d is dead\n" RESET, time_since_dinner_starts(),
				philo->number);
			pthread_mutex_unlock(&philo->eat_mtx);
			return ;
		}
		pthread_mutex_unlock(&philo->eat_mtx);
		i++;
	}
	return ;
}
