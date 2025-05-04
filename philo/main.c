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

// checker
// philos number must not be 0

void	wash_dishes(pthread_mutex_t *forks, pthread_t *threads,
		int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
		pthread_join(threads[i++], NULL);
	i = 0;
	while (i < num_of_philos)
		pthread_mutex_destroy(&forks[i++]);
}

unsigned int	ft_atoi(char *s)
{
	unsigned long	n;

	n = 0;
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + *s++ - '0';
		if (n >= INT_MAX)
			return (INT_MAX);
	}
	if (*s)
		return (INT_MAX);
	return (n);
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
		philos[i].left_fork = forks + i;
		philos[i].right_fork = forks + ((i + 1) % num_of_philos);
		philos[i].number = i + 1;
		philos[i].eat_times = 0;
		philos[i].dinner_status = 1;
		i++;
	}
}

int	args_is_valid(t_philo philo)
{
	if (philo.ttd == INT_MAX || philo.tte == INT_MAX || philo.tts == INT_MAX)
		return (0);
	if (philo.ttd < 60 || philo.tte < 60 || philo.tts < 60)
		return (0);
	if (philo.num_of_philos > 200 || philo.num_of_philos == 0)
		return (0);
	if (philo.must_eat_times == INT_MAX)
		return (0);
	return (1);
}

int	main(int ac, char *av[])
{
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_t		threads[MAX_PHILOS];

	if (ac != 5 && ac != 6)
		return (1);
	init_philos(ac, av, philos, forks);
	if (args_is_valid(philos[0]) == 0)
	{
		printf("INVALID ARGUMENTS\n");
		return (1);
	}
	init_forks(forks, philos[0].num_of_philos);
	run_threads(philos, threads);
	while (philos[0].dinner_status == 1)
	{
		check_philos_full(philos);
		check_starvation(philos);
	}
	wash_dishes(forks, threads, philos[0].num_of_philos);
	return (0);
}
