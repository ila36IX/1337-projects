/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:46:01 by aljbari           #+#    #+#             */
/*   Updated: 2025/05/03 16:20:05 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_PHILOS 200
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"

typedef time_t		t_microsec;

enum
{
	GET,
	SET
};

typedef struct s_philo
{
	int				num_of_philos;
	int				dinner_status;
	int				number;
	int				must_eat_times;
	int				eat_times;
	int				ttd;
	int				tts;
	int				tte;
	time_t			last_meal_time;
	pthread_mutex_t	eat_mtx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*status_mtx;
}					t_philo;

void				*thread_func(void *p);
t_microsec			curr_time(void);
t_microsec			time_since_dinner_starts(void);
void				start_dinner_clock(void);
void				check_philos_full(t_philo *philos);
void				check_starvation(t_philo *philos);
void				ft_usleep(t_microsec amount, t_philo *philo);
void				log_action(char *action, t_philo *philo);
void				init_forks(pthread_mutex_t *forks, int num_of_forks);
void				run_threads(t_philo *philos, pthread_t *threads);
