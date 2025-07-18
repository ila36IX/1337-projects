/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:03:29 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/18 01:03:29 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# define PHILO_MAX_NUMBER 200
# define SEM_SIM_STATUS "/sim_status"
# define SEM_WRITE "/philo_write"
# define SEM_FORKS "/philo_forks"
# define SEM_FULL "/philo_full"
# define RESET "\x1b[0m"
# define BOLD "\x1b[1m"
# define YELLOW "\x1b[33m"
# define RED "\x1b[31m"

typedef struct s_info
{
	int				nbr;
	int				ttd;
	int				tte;
	int				tts;
	int				time_of_eats;
	sem_t			*sem_write;
	sem_t			*sem_sim_status;
	sem_t			*sem_forks;
	sem_t			*sem_full;
}					t_info;

typedef struct s_philo
{
	int				eat_times;
	int				id;
	int				sim_status;
	pid_t			pid;
	time_t			last_eat_time;
	t_info			info;
	pthread_mutex_t	mtx;
	pthread_mutex_t	mtx_sim_status;
}					t_philo;

void				*am_alive(void *_philo);
void				*sim_status_func(void *_philo);
time_t				curr_time(void);
void				unlock_semaphores(t_philo *philo);
void				start_dinner_clock(void);
time_t				time_since_dinner_starts(void);
void				philo_life(t_philo *philo);
bool				philo_try_take_forks(t_philo *philo);
void				ft_usleep(time_t milliseconds, t_philo *philo);
void				log_action(char *str, t_philo *philo);
void				start_philo_process(t_philo *philo);
void				unlock_semaphores(t_philo *philo);
void				main_release_semaphores(t_info *info);
void				process_release_resources(t_philo *philo);
void				start_simulation(t_philo *philos);
void				*check_full(void *_philos);
unsigned int		ft_atoi(char *s);
void				start_dinner_clock(void);
time_t				curr_time(void);

#endif
