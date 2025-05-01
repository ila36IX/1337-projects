#include "philo.h"
#include <stdio.h>
#include <unistd.h>


void     update_philo_meals_count(int philo)
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        if (shared->must_eat_times == -1)
                return ;
        shared->philo_eat_times[philo]++;
}

void philo_life(int philo)
{

        pthread_mutex_lock(left_fork(philo));
        printf("%ld %d has taken a fork\n", time_since_dinner_starts(), philo);
        pthread_mutex_lock(right_fork(philo));
        printf("%ld %d has taken a fork\n", time_since_dinner_starts(), philo);
        printf("%ld %d is eating\n",time_since_dinner_starts(), philo);
        update_last_meal_time(philo);
        update_philo_meals_count(philo);
        wait_in_mili(time_to_eat());
        pthread_mutex_unlock(left_fork(philo));
        pthread_mutex_unlock(right_fork(philo));
        printf("%ld %d is sleeping\n", time_since_dinner_starts(), philo);
        wait_in_mili(time_to_sleep());
        printf("%ld %d is thinking\n", time_since_dinner_starts(), philo);
}

int     all_meals_eaten()
{
        int philo;
        t_shared *shared;

        shared = shared_mem(GET, NULL);

        philo = 0;
        while(philo < shared->n)
        {
                if (shared->philo_eat_times[philo] != shared->must_eat_times)
                        return (0);
                philo++;
        }
        return (1);
}

int     nobody_dies()
{
        int philo;
        t_shared *shared;
        time_t last_meal_time;

        shared = shared_mem(GET, NULL);

        philo = 0;
        while(philo < shared->n)
        {
                last_meal_time = time_after_last_meal(philo);
                if (last_meal_time > shared->ttd && shared->philo_eat_times[philo] != shared->must_eat_times)
                {
                        shared->died_philo = philo;
                        shared->time_of_death = last_meal_time;
                        return (0);
                }
                philo++;
        }
        return (1);
}

int     dead_philo()
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        return (shared->died_philo);
}


int     philo_eats_enough(int philo)
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        if (shared->must_eat_times == -1)
                return (0);
        if (shared->philo_eat_times[philo] == shared->must_eat_times)
                return (1);
        return (0);
}

void *thread_func(void *p)
{
        int philo;

        philo = (long) p;
        if (philo_birthtime(philo) == 0)
                init_philo_birth(philo);
        if (philo % 2)
                wait_in_mili(1);
        while (dead_philo() == -1 && !philo_eats_enough(philo))
        {
                philo_life(philo);
        }
        return (NULL);
}

void run_dinner_clock(void);

int main(int ac, char *av[])
{
        t_shared shared;
        pthread_t threads[MAX_PHILOS];
        int i;

        if (ac != 5 && ac != 6)
                return (1);
        else
        {
                shared.n = atoi(av[1]);
                shared.ttd = atoi(av[2]);
                shared.tte = atoi(av[3]);
                shared.tts = atoi(av[4]);
                shared.died_philo = -1;
                if (ac == 6)
                        shared.must_eat_times = atoi(av[5]);
                else
                        shared.must_eat_times = -1;
        }

        shared_mem(SET, &shared);
        bzero(shared.birthtimes, sizeof(shared.birthtimes));
        i = 0;
        while (i < shared.n)
        {
                pthread_mutex_init(&shared.forks[i], NULL);
                i++;
        }
        i = 0;
        run_dinner_clock();
        while (i < shared.n)
        {
                shared.last_meal[i] = curr_time();
                pthread_create(&threads[i], NULL, thread_func, (void *) (long)i);
                i++;
        }
        i = 0;
        while (i < shared.n)
                pthread_detach(threads[i++]);
        while (nobody_dies())
        {
                if (all_meals_eaten())
                        break;
                wait_in_mili(5);
        }
        if (dead_philo() != -1)
                printf("%ld %d is dead\n", time_since_dinner_starts(), dead_philo());
        return (0);
}
