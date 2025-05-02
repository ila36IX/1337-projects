#include "philo.h"
void    log_action(char *action, t_philo *philo);

void philo_life(t_philo *philo)
{
        pthread_mutex_lock(&philo->left_fork);
        log_action("has taken a fork", philo);
        pthread_mutex_lock(&philo->right_fork);
        log_action("has taken a fork", philo);
        log_action("is eating", philo);
        philo->last_meal_time = curr_time();
        philo->eat_times++;
        wait_in_mili(philo->tte);
        pthread_mutex_unlock(&philo->left_fork);
        pthread_mutex_unlock(&philo->right_fork);
        log_action("is sleeping", philo);
        wait_in_mili(philo->tts);
        log_action("is thinking", philo);
}

void *thread_func(void *p)
{
        t_philo *philo;

        philo = p;
        philo->birthtime = curr_time();
        if (philo->number % 2 != 0)
                wait_in_mili(1);
        while (philo->dinner_status == 1)
                philo_life(philo);
        return (NULL);
}
