#include <stdio.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_PHILOS 200
typedef time_t microsec_t;

enum
{
        GET,
        SET
};

typedef struct {
        int num_of_philos;
        int dinner_status;
        int number;
        int must_eat_times;
        int eat_times;
        int died_philo;
        int ttd;
        int tts;
        int tte;
        time_t time_of_death;
        time_t dinner_starts_time;
        time_t birthtime;
        time_t last_meal_time;
        pthread_mutex_t left_fork;
        pthread_mutex_t right_fork;
} t_philo;

void *thread_func(void *);
void init_philo_birth(int philo);
microsec_t  curr_time();
void wait_in_mili(microsec_t amount);
microsec_t time_since_dinner_starts(void);
void start_dinner_clock(void);
void    check_philos_full(t_philo *philos);
void     check_starvation(t_philo *philos);
