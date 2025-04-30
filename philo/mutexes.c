
#include "philo.h"

pthread_mutex_t *left_fork(int philo)
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        return (&shared->forks[philo]);
}

pthread_mutex_t *right_fork(int philo)
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        return (&shared->forks[(philo + 1) % shared->n]);
}

pthread_mutex_t *mutex_write()
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        return (&shared->lock_write);
}
