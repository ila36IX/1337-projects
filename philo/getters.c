#include "philo.h"

void *shared_mem(int flag, void *value)
{
        static void *shared;

        if (flag == GET)
                return (shared);
        if (flag == SET)
                shared = value;
        return (shared);
}

microsec_t time_to_eat()
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        return (shared->tte);
}

microsec_t time_to_sleep()
{
        t_shared *shared;

        shared = shared_mem(GET, NULL);
        return (shared->tts);
}
