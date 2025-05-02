#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// checker
// philos number must not be 0

void wash_dishes(pthread_mutex_t *forks, pthread_t *threads, int num_of_philos)
{
        int i;
 
        i = 0;
        while (i < num_of_philos)
                pthread_join(threads[i++], NULL);
        i = 0;
        while (i < num_of_philos)
                pthread_mutex_destroy(&forks[i++]);
}

void    init_philos(int ac, char **av, t_philo *philos, pthread_mutex_t *forks)
{
        int i;
        int num_of_philos;

        num_of_philos = atoi(av[1]);
        i = 0;
        while (i < num_of_philos)
        {
                philos[i].num_of_philos = atoi(av[1]);
                philos[i].ttd = atoi(av[2]);
                philos[i].tte = atoi(av[3]);
                philos[i].tts = atoi(av[4]);
                philos[i].died_philo = -1;
                if (ac == 6)
                        philos[i].must_eat_times = atoi(av[5]);
                else
                        philos[i].must_eat_times = -1;
                philos[i].left_fork = forks[i];
                philos[i].left_fork = forks[(i + 1) % num_of_philos];
                philos[i].number = i + 1;
                philos[i].eat_times = 0;
                philos[i].dinner_status = 1;
                i++;
        }
}

void init_forks(pthread_mutex_t *forks, int num_of_forks)
{
        int i;

        i = 0;
        while (i < num_of_forks)
                pthread_mutex_init(&forks[i++], NULL);
}

void run_threads(t_philo *philos, pthread_t *threads)
{
        int i;

        i = 0;
        while (i < philos[0].num_of_philos)
        {
                philos[i].last_meal_time = curr_time();
                pthread_create(&threads[i], NULL, thread_func, &philos[i]);
                i++;
        }
}

int main(int ac, char *av[])
{
        t_philo philos[MAX_PHILOS];
        pthread_mutex_t forks[MAX_PHILOS];
        pthread_t threads[MAX_PHILOS];

        if (ac != 5 && ac != 6)
                return (1);
        init_philos(ac, av, (t_philo *)&philos, (pthread_mutex_t *)&forks);
        // check args
        init_forks((pthread_mutex_t *)&forks, philos[0].num_of_philos);
        start_dinner_clock();
        run_threads((t_philo *) philos, (pthread_t *)threads);
        while (philos[0].dinner_status == 1)
        {
                check_philos_full((t_philo *)&philos);
                check_starvation((t_philo *)&philos);
        }
        if (philos[0].died_philo != -1)
                printf("%ld %d is dead\n", philos[0].time_of_death, philos[0].died_philo);
        wash_dishes((pthread_mutex_t *)&forks, (pthread_t *)&threads, philos[0].num_of_philos);
        return (0);
}
