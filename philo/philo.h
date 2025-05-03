/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:46:01 by aljbari           #+#    #+#             */
/*   Updated: 2025/05/03 15:48:50 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_PHILOS 200

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
	time_t			dinner_starts_time;
	time_t			birthtime;
	time_t			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

void				*thread_func(void *p);
void				init_philo_birth(int philo);
t_microsec			curr_time(void);
void				wait_in_mili(t_microsec amount);
t_microsec			time_since_dinner_starts(void);
void				start_dinner_clock(void);
void				check_philos_full(t_philo *philos);
void				check_starvation(t_philo *philos);
