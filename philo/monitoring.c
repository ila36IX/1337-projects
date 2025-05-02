#include "philo.h"

void    set_dinner_as_over(t_philo *philos)
{
        int i;

        i = 0;
        while(i < philos[0].num_of_philos)
                philos[i++].dinner_status = 0;
}


void    log_action(char *action, t_philo *philo)
{
        if (philo->dinner_status == 0)
                return ;
        printf("%ld %d %s\n", time_since_dinner_starts(), philo->number, action);
}

/**
 * check_philos_full - check if all philosophers eats at least
 * number_of_times_each_philosopher_must_eat times, if true the dinner status
 * of all philosophers will set to 0
 *
 * @philos: list of all philosophers, at least one should exist
 *
 * Return: Nothing
 */
void    check_philos_full(t_philo *philos)
{
        int i;

        if (philos[0].must_eat_times == -1)
                return ;
        i = 0;
        while(i < philos[0].num_of_philos)
        {
                if (philos[i].eat_times < philos[i].must_eat_times)
                        return ;
                i++;
        }
        set_dinner_as_over(philos);
        return ;
}

/**
 * starvation_not_found - Check if all philosophers is alive, if a dead
 * one found the dinner status of all philosophers will be set to 0
 *
 * @philos: list of all philosophers, at least one should exist
 *
 * Return: Nothing
 */
void     check_starvation(t_philo *philos)
{
        t_philo *philo;
        int i;


        i = 0;
        while(i < philos[0].num_of_philos)
        {
                philo = &philos[i];
                if (curr_time() - philo->last_meal_time > philo->ttd)
                {
                        philo->died_philo = philo->number;
                        philo->time_of_death = time_since_dinner_starts();
                        printf("is problem from here? %ld\n", curr_time() - philo->last_meal_time);
                        set_dinner_as_over(philos);
                        return ;
                }
                i++;
        }
        return ;
}
