#include <stdio.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_PHILOS 200
#define TO_MILI(n) ((n) * 1000)
typedef time_t microsec_t;

enum
{
        GET,
        SET
};

typedef struct {
        int n;
        int must_eat_times;
        time_t ttd;
        time_t tts;
        time_t tte;
        time_t dinner_time;
        int died_philo;
        int time_of_death;
        int philo_eat_times[MAX_PHILOS];
        microsec_t birthtimes[MAX_PHILOS];
        microsec_t last_meal[MAX_PHILOS];
        pthread_mutex_t forks[MAX_PHILOS];
        pthread_mutex_t lock_write;
} t_shared;

void *thread_func(void *);
void init_philo_birth(int philo);
microsec_t philo_birthtime(int philo);
microsec_t philo_age(int philo);
pthread_mutex_t *left_fork(int philo);
pthread_mutex_t *mutex_write();
pthread_mutex_t *right_fork(int philo);
microsec_t time_to_sleep();
microsec_t time_to_eat();
void *shared_mem(int flag, void *value);
microsec_t  curr_time();
void wait_in_mili(microsec_t amount);
microsec_t time_since_dinner_starts(void);
void update_last_meal_time(int philo);
void update_last_meal_time(int philo);
time_t get_last_meal_time(int philo);
