#include <pthread.h>
#include <signal.h>
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>


void	start_dinner_clock(void);
time_t	curr_time(void);
const char *semName = "/philo_forks";




time_t	time_since_dinner_starts(void)
{
	static time_t	dinner_start_clock;

	if (dinner_start_clock)
		return (curr_time() - dinner_start_clock);
	else
		dinner_start_clock = curr_time();
	return (curr_time() - dinner_start_clock);
}

void	start_dinner_clock(void)
{
	time_since_dinner_starts();
}


time_t	curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

time_t ttd = 2000;

typedef struct s_info {
	int	nbr; // number f philos
	int	ttd;
	int	tte;
	int	tts;
} t_info;

typedef struct s_philo {
	time_t last_eat_time;
	int id;
	pthread_mutex_t mtx;
	t_info info;

} t_philo;


void *monitor_func(void *_philo)
{
	t_philo *philo;

	philo = _philo;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx);
		if (curr_time() - philo->last_eat_time > philo->info.ttd)
		{
			pthread_mutex_unlock(&philo->mtx);
			exit(philo->id);
		}
		pthread_mutex_unlock(&philo->mtx);
	}	
}

void philo(int id, t_info info)
{
	pthread_t monitor;
	t_philo philo = {
		.mtx = PTHREAD_MUTEX_INITIALIZER,
		.last_eat_time = curr_time(),
		.id = id,
		.info = info,
	};

	pthread_create(&monitor, NULL, monitor_func, &philo);
	sem_t *sem_id = sem_open(semName, 0);
	if (sem_id == SEM_FAILED)
	{
		perror("philo-sem-open");
		exit(1);
	}
	printf("(%ld) %d is born!\n", time_since_dinner_starts(), id);
	while (1)
	{
		if (sem_wait(sem_id) == -1)
		{
			perror("philo-sem-wait");
			exit(1);
		}
		printf("(%ld) %d has taken a fork!\n", time_since_dinner_starts(), id);
		if (sem_wait(sem_id) == -1)
		{
			perror("philo-sem-wait");
			exit(1);
		}
		pthread_mutex_lock(&philo.mtx);
		philo.last_eat_time = curr_time();
		pthread_mutex_unlock(&philo.mtx);
		printf("(%ld) %d has taken a fork!\n", time_since_dinner_starts(), id);
		printf("(%ld) %d is eating!\n", time_since_dinner_starts(),id);
		usleep(info.tte * 1000);
		if (sem_post(sem_id) == -1)
		{
			perror("philo-sem-post");
			exit(1);
		}
		if (sem_post(sem_id) == -1)
		{
			perror("philo-sem-post");
			exit(1);
		}
		printf("(%ld) %d is sleeping\n", time_since_dinner_starts(), id);
		usleep(info.tts * 1000);
		printf("(%ld) %d is thinking\n", time_since_dinner_starts(), id);
	}
}


void run_philos(int *pids, t_info info)
{
	pid_t pid;

	start_dinner_clock();
	for (int i = 0; i < info.nbr; i += 2)
	{
		pid = fork();
		if (pid == 0)
		{
			philo(i + 1, info);
		}
		pids[i] = pid;
	}
	usleep(500);
	for (int i = 1; i < info.nbr; i += 2)
	{
		pid = fork();
		if (pid == 0)
		{
			philo(i + 1, info);
		}
		pids[i] = pid;
	}
}

#define PHILO_MAX_NUMBER 200

int main(int ac, char **av)
{
	int pids[PHILO_MAX_NUMBER];


	sem_unlink(semName);


	if (ac != 5 && ac != 6)
		return (0);
	t_info info = {
		.nbr = atoi(av[1]),
		.ttd = atoi(av[2]),
		.tte = atoi(av[3]),
		.tts = atoi(av[4]),
	};
	if (sem_open(semName, O_CREAT | O_EXCL, 0600, info.nbr) == SEM_FAILED)
	{
		perror("main-sem-open");
		exit(1);
	}
	run_philos(pids, info);

	int exit_status;
	pid_t pid = waitpid(-1, &exit_status, 0);
	for (int i = 0; i < info.nbr; i++)
	{
		if (pids[i] != pid)
			kill(pids[i], SIGTERM);
		else {
			printf("(%ld) %d is dead\n", time_since_dinner_starts(), i + 1);
		}
	}
	sem_unlink(semName);
	return 0;
}

