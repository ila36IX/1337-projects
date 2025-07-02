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


#define SEM_SIM_STATUS "/sim_status"
#define SEM_WRITE      "/philo_write"
#define SEM_FORKS      "/philo_forks"

#define RESET          "\x1b[0m"
#define BOLD           "\x1b[1m"
#define YELLOW         "\x1b[33m"
#define RED            "\x1b[31m"



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

typedef struct s_info {
	int	nbr; // number f philos
	int	ttd;
	int	tte;
	int	tts;
	sem_t *sem_write;
	sem_t *sem_sim_status;
	sem_t *sem_forks;
} t_info;

typedef struct s_philo {
	time_t last_eat_time;
	int id;
	pthread_mutex_t mtx;
	t_info info;
	pid_t pid;
} t_philo;

/**
 * am_alive - thread function that keeps checking if philosopher last eat time
 * does cause death
 *
 * @_philo: philo infos
 * Return: Nothing, the function will keep checking until it got stopped by
 * SIGTERM signal, or if it exits
 */
void *am_alive(void *_philo)
{
	t_philo *philo;

	philo = _philo;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx);
		if (curr_time() - philo->last_eat_time > philo->info.ttd)
		{
			pthread_mutex_unlock(&philo->mtx);
			sem_post(philo->info.sem_sim_status);
			if (sem_wait(philo->info.sem_write) == -1)
			{
				perror("monitor_func_sem_wait_write:");
				exit(1);
			}
			printf("%ld %d is dead\n", time_since_dinner_starts(), philo->id);
			sem_post(philo->info.sem_sim_status);
			exit(0);
		}
		pthread_mutex_unlock(&philo->mtx);
	}	
}

	void init_simaphors(t_info *info);
/**
 * philo_life - the miserable life of a philospher
 * take fork - eat - sleep - think - repeat waiting for its death
 */
void philo_life(t_philo *philo)
{
	int value;
	while (1)
	{
		sem_getvalue(philo->info.sem_forks, &value);
		printf("Current value: %d\n", value);
		if (sem_wait(philo->info.sem_forks) == -1)
		{
			perror("philo-sem-wait");
			exit(1);
		}
		printf("(%ld) %d has taken a fork!\n", time_since_dinner_starts(), philo->id);
		if (sem_wait(philo->info.sem_forks) == -1)
		{
			perror("philo-sem-wait");
			exit(1);
		}
		if (pthread_mutex_lock(&philo->mtx) == -1)
		{
			perror("philo-sem-wait");
			exit(1);
		}
		philo->last_eat_time = curr_time();
		pthread_mutex_unlock(&philo->mtx);
		printf("(%ld) %d has taken a fork!\n", time_since_dinner_starts(), philo->id);
		printf("(%ld) %d is eating!\n", time_since_dinner_starts(),philo->id);
		usleep(philo->info.tte * 1000);
		if (sem_post(philo->info.sem_forks) == -1)
		{
			perror("philo-sem-post");
			exit(1);
		}
		if (sem_post(philo->info.sem_forks) == -1)
		{
			perror("philo-sem-post");
			exit(1);
		}
		printf("(%ld) %d is sleeping\n", time_since_dinner_starts(), philo->id);
		usleep(philo->info.tts * 1000);
		printf("How many times??\n");
	}
}

void *sim_status_func(void *_philo)
{
	t_philo *philo;
	
	philo = _philo;
	if (sem_wait(philo->info.sem_write) == -1)
	{
		perror("sem_wait:");
		exit(1);
	}
	sem_close(philo->info.sem_write);
	exit(0);
	return (NULL);
}

void	log_action(char *action, t_philo *philo)
{
	if (sem_wait(philo->info.sem_write) != -1)
	{
		perror("sem_write_log_action:");
		exit(1);
	}
	printf(YELLOW "%ld" RESET " " BOLD "%d " RESET "%s\n",
		time_since_dinner_starts(), philo->id, action);
	if (sem_post(philo->info.sem_write) != -1)
	{
		perror("sem_write_log_action:");
		exit(1);
	}
}

void philo_process(t_philo *philo)
{
	// pthread_t monitor;
	// pthread_t sim_status;


	if (philo->id % 2)
		usleep(500);
	
	philo_life(philo);
	// pthread_create(&monitor, NULL, am_alive, &philo);
	// pthread_detach(monitor);
	// pthread_create(&sim_status, NULL, sim_status_func, &philo);
	// pthread_detach(sim_status);
}

void start_simulation(t_philo *philos)
{
	pid_t pid;
	int i;

	start_dinner_clock();
	i = 0;
	while (i < philos[0].info.nbr)
	{
		philos[i].last_eat_time = curr_time();
		pid = fork();
		philos[i].pid = pid;
		if (pid == -1)
		{
			perror("fork: ");
			exit(1);
		}
		if (pid == 0)
		{
			philo_process(&philos[i]);
			printf("WHa the fck?\n");
		}
		i++;
	}
}

void init_philos(t_philo *philos, t_info info)
{
	int i;

	i = 0;
	while (i < info.nbr)
	{
		pthread_mutex_init(&philos[i].mtx, NULL);
		philos[i].id = i + 1;
		philos[i].info = info,
		i++;
	}
}


#define PHILO_MAX_NUMBER 200
void init_simaphors(t_info *info)
{
	// unlink(SEM_FORKS);
	// unlink(SEM_WRITE);
	// unlink(SEM_SIM_STATUS);
	info->sem_forks = sem_open(SEM_FORKS,  O_CREAT | O_TRUNC, 0644, info->nbr);
	if (info->sem_forks == SEM_FAILED)
	{
		perror("sem_open_init_semaphore");
		exit(1);
	}
	info->sem_write = sem_open(SEM_WRITE,  O_CREAT | O_TRUNC, 0644, 1);
	if (info->sem_write == SEM_FAILED)
	{
		perror("sem_open_init_semaphore");
		exit(1);
	}
	info->sem_sim_status = sem_open(SEM_SIM_STATUS,  O_CREAT | O_TRUNC, 0644, 0);
	if (info->sem_sim_status == SEM_FAILED)
	{
		perror("sem_open_init_semaphore");
		exit(1);
	}
}

int main(int ac, char **av)
{
	t_philo philos[PHILO_MAX_NUMBER];

	if (ac != 5 && ac != 6)
		return (0);
	t_info info = {
		.nbr = atoi(av[1]),
		.ttd = atoi(av[2]),
		.tte = atoi(av[3]),
		.tts = atoi(av[4]),
	};
	init_simaphors(&info);
	init_philos(philos, info);
	start_simulation(philos);
	
	int status;
	waitpid(-1, &status, 0);
	printf("Exits with: %d\n", status);;
	return 0;
}

