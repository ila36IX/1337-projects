#include "philo.h"

void start_dinner_clock(void)
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
        usleep(amount * 1000);
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
