#include "philo.h"

void run_dinner_clock(void)
{
        time_since_dinner_starts();
}

microsec_t  curr_time()
{
        struct timeval tv;

        gettimeofday(&tv, NULL);
        return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void wait_in_mili(microsec_t amount)
{
        usleep(TO_MILI(amount));
}

microsec_t time_since_dinner_starts(void)
{
        static time_t dinner_start_clock;

        if (dinner_start_clock)
                return (curr_time() - dinner_start_clock);
        else
                dinner_start_clock = curr_time();
        return (curr_time() - dinner_start_clock);
}

void update_last_meal_time(int philo)
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        shared->last_meal[philo] = curr_time();
}

microsec_t time_after_last_meal(int philo)
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        return (curr_time() - shared->last_meal[philo]);
}
