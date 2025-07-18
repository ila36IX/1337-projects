/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:52:31 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/18 02:52:31 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_philo *philos, t_info info)
{
	int	i;

	i = 0;
	while (i < info.nbr)
	{
		pthread_mutex_init(&philos[i].mtx, NULL);
		pthread_mutex_init(&philos[i].mtx_sim_status, NULL);
		philos[i].id = i + 1;
		philos[i].info = info;
		philos[i].eat_times = 0;
		philos[i].sim_status = 1;
		i++;
	}
}

void	init_simaphors(t_info *info)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_SIM_STATUS);
	sem_unlink(SEM_FULL);
	info->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_TRUNC, 0644, info->nbr);
	if (info->sem_forks == SEM_FAILED)
		exit(1);
	info->sem_write = sem_open(SEM_WRITE, O_CREAT | O_TRUNC, 0644, 1);
	if (info->sem_write == SEM_FAILED)
		exit(1);
	info->sem_sim_status = sem_open(SEM_SIM_STATUS, O_CREAT | O_TRUNC, 0644, 0);
	if (info->sem_sim_status == SEM_FAILED)
		exit(1);
	info->sem_full = sem_open(SEM_FULL, O_CREAT | O_TRUNC, 0644, 0);
	if (info->sem_full == SEM_FAILED)
		exit(1);
}

bool	init_info(int ac, char **av, t_info *info)
{
	if (ac != 5 && ac != 6)
		return (0);
	info->nbr = ft_atoi(av[1]);
	info->ttd = ft_atoi(av[2]);
	info->tte = ft_atoi(av[3]);
	info->tts = ft_atoi(av[4]);
	if (ac == 6)
		info->time_of_eats = ft_atoi(av[5]);
	else
		info->time_of_eats = -1;
	if (info->ttd == INT_MAX || info->tte == INT_MAX || info->tts == INT_MAX)
		return (false);
	if (info->ttd < 60 || info->tte < 60 || info->tts < 60)
		return (false);
	if (info->nbr > 200 || info->nbr == 0 || info->time_of_eats == INT_MAX
		|| info->time_of_eats == 0)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_philo		philos[PHILO_MAX_NUMBER];
	int			i;
	pthread_t	full_thread;
	t_info		info;

	if (!init_info(ac, av, &info))
	{
		printf("UNVALID ARGUMENT\n");
		return (1);
	}
	init_simaphors(&info);
	init_philos(philos, info);
	start_simulation(philos);
	pthread_create(&full_thread, NULL, check_full, &philos);
	pthread_detach(full_thread);
	i = 0;
	while (i < info.nbr)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	main_release_semaphores(&info);
	return (0);
}
