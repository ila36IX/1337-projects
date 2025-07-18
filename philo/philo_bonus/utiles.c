/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:21:48 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/18 01:21:48 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlock_semaphores(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info.nbr)
	{
		sem_post(philo->info.sem_full);
		sem_post(philo->info.sem_forks);
		sem_post(philo->info.sem_sim_status);
		i++;
	}
}

void	main_release_semaphores(t_info *info)
{
	sem_close(info->sem_forks);
	sem_close(info->sem_write);
	sem_close(info->sem_sim_status);
	sem_close(info->sem_full);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_SIM_STATUS);
	sem_unlink(SEM_FULL);
}

void	process_release_resources(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info.nbr)
	{
		sem_post(philo->info.sem_full);
		sem_post(philo->info.sem_write);
		sem_post(philo->info.sem_forks);
		i++;
	}
	sem_close(philo->info.sem_forks);
	sem_close(philo->info.sem_write);
	sem_close(philo->info.sem_sim_status);
	sem_close(philo->info.sem_full);
}
