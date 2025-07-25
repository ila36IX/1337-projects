/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:44:02 by aljbari           #+#    #+#             */
/*   Updated: 2025/05/03 16:25:35 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	assign_forks(int i, t_philo *philo, pthread_mutex_t *forks)
{
	if (i % 2)
	{
		philo->left_fork = forks + i;
		philo->right_fork = forks + ((i + 1) % philo->num_of_philos);
	}
	else
	{
		philo->right_fork = forks + i;
		philo->left_fork = forks + ((i + 1) % philo->num_of_philos);
	}
}

void	init_philos(int ac, char **av, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;
	int	num_of_philos;

	num_of_philos = ft_atoi(av[1]);
	i = 0;
	while (i < num_of_philos)
	{
		philos[i].num_of_philos = num_of_philos;
		philos[i].ttd = ft_atoi(av[2]);
		philos[i].tte = ft_atoi(av[3]);
		philos[i].tts = ft_atoi(av[4]);
		if (ac == 6)
			philos[i].must_eat_times = ft_atoi(av[5]);
		else
			philos[i].must_eat_times = -1;
		assign_forks(i, &philos[i], forks);
		philos[i].number = i + 1;
		philos[i].eat_times = 0;
		philos[i].dinner_status = 1;
		i++;
	}
}

void	init_philo_mutexes(t_philo *philos, pthread_mutex_t *status_mtx)
{
	int	i;

	pthread_mutex_init(status_mtx, NULL);
	i = 0;
	while (i < philos[0].num_of_philos)
	{
		philos[i].status_mtx = status_mtx;
		pthread_mutex_init(&philos[i].eat_mtx, NULL);
		i++;
	}
}

int	args_is_valid(int ac, char **av)
{
	int	num_of_philos;
	int	ttd;
	int	tte;
	int	tts;

	if (ac != 5 && ac != 6)
		return (0);
	num_of_philos = ft_atoi(av[1]);
	ttd = ft_atoi(av[2]);
	tte = ft_atoi(av[3]);
	tts = ft_atoi(av[4]);
	if (ttd == INT_MAX || tte == INT_MAX || tts == INT_MAX)
		return (0);
	if (ttd < 60 || tte < 60 || tts < 60)
		return (0);
	if (num_of_philos > 200 || num_of_philos <= 0)
		return (0);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) == INT_MAX || ft_atoi(av[5]) == 0)
			return (0);
	}
	return (1);
}

int	main(int ac, char *av[])
{
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	status_mtx;
	t_philo			philos[MAX_PHILOS];
	pthread_t		threads[MAX_PHILOS];

	if (args_is_valid(ac, av) == 0)
	{
		printf("INVALID ARGUMENTS\n");
		return (1);
	}
	init_philos(ac, av, philos, forks);
	init_philo_mutexes(philos, &status_mtx);
	init_forks(forks, philos[0].num_of_philos);
	run_threads(philos, threads);
	while (philos[0].dinner_status == 1)
	{
		if (philos[0].must_eat_times != -1)
			check_philos_full(philos);
		check_starvation(philos);
	}
	wash_dishes(philos, forks, threads);
	return (0);
}
