#include "philo.h"

void init_philo_birth(int philo)
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        shared->birthtimes[philo] = curr_time();
}

microsec_t philo_birthtime(int philo)
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        return (shared->birthtimes[philo]);
}



microsec_t philo_age(int philo)
{
        return (curr_time() - philo_birthtime(philo));
}

