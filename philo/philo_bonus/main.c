#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define PHILO_MAX_NUMBER 200
void				start_dinner_clock(void);
time_t				curr_time(void);

#define SEM_SIM_STATUS "/sim_status"
#define SEM_WRITE "/philo_write"
#define SEM_FORKS "/philo_forks"
#define SEM_FULL "/philo_full"

#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"

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

typedef struct s_info
{
	int nbr; // number f philos
	int				ttd;
	int				tte;
	int				tts;
	int				time_of_eats;
	sem_t			*sem_write;
	sem_t			*sem_sim_status;
	sem_t			*sem_forks;
	sem_t			*sem_full;
}					t_info;

typedef struct s_philo
{
	int				eat_times;
	int				id;
	int				sim_status;
	pid_t			pid;
	time_t			last_eat_time;
	t_info			info;
	pthread_mutex_t	mtx;
	pthread_mutex_t	mtx_sim_status;
}					t_philo;

void	*sim_status_func(void *_philo)
{
	t_philo	*philo;

	philo = _philo;
	sem_wait(philo->info.sem_sim_status);
	sem_post(philo->info.sem_sim_status);
	sem_wait(philo->info.sem_write);
	pthread_mutex_lock(&philo->mtx_sim_status);
	philo->sim_status = 0;
	pthread_mutex_unlock(&philo->mtx_sim_status);
	sem_post(philo->info.sem_write);
	return (NULL);
}

/**
 * am_alive - thread function that keeps checking if philosopher last eat time
 * does cause death
 *
 * @_philo: philo infos
 * Return: Nothing, the function will keep checking until it got stopped by
 * SIGTERM signal, or if it exits
 */
void	*am_alive(void *_philo)
{
	t_philo	*philo;

	philo = _philo;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx);
		if (curr_time() - philo->last_eat_time > philo->info.ttd)
		{
			pthread_mutex_unlock(&philo->mtx);
			sem_wait(philo->info.sem_write);
			printf("%ld %d is dead\n", time_since_dinner_starts(), philo->id);
			sem_post(philo->info.sem_sim_status);
			sem_post(philo->info.sem_sim_status);
			sem_post(philo->info.sem_write);
			return (0);
		}
		pthread_mutex_unlock(&philo->mtx);
	}
}

void	log_action(char *action, t_philo *philo)
{
	sem_wait(philo->info.sem_write);
	pthread_mutex_lock(&philo->mtx_sim_status);
	if (philo->sim_status)
		printf(YELLOW "%ld" RESET " " BOLD "%d " RESET "%s\n",
			time_since_dinner_starts(), philo->id, action);
	pthread_mutex_unlock(&philo->mtx_sim_status);
	sem_post(philo->info.sem_write);
}

void	ft_usleep(time_t milliseconds, t_philo *philo)
{
	time_t	start;

	start = curr_time();
	while ((curr_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&philo->mtx_sim_status);
		if (!philo->sim_status)
			break ;
		pthread_mutex_unlock(&philo->mtx_sim_status);
		usleep(500);
	}
	pthread_mutex_unlock(&philo->mtx_sim_status);
}



/**
 * philo_life - the miserable life of a philospher
 * take fork - eat - sleep - think - repeat waiting for its death
 */
void	philo_life(t_philo *philo)
{
	while (1)
	{

		pthread_mutex_lock(&philo->mtx_sim_status);
		if (!philo->sim_status)
		{
			pthread_mutex_unlock(&philo->mtx_sim_status);
			return ;
		}
		pthread_mutex_unlock(&philo->mtx_sim_status);
		sem_wait(philo->info.sem_forks);
		log_action("has taken a fork", philo);
		sem_wait(philo->info.sem_forks);
		pthread_mutex_lock(&philo->mtx);
		philo->last_eat_time = curr_time();
		philo->eat_times++;
		if (philo->eat_times == philo->info.time_of_eats)
			sem_post(philo->info.sem_full);
		pthread_mutex_unlock(&philo->mtx);
		log_action("has taken a fork!", philo);
		log_action("is eating", philo);
		ft_usleep(philo->info.tte, philo);
		sem_post(philo->info.sem_forks);
		sem_post(philo->info.sem_forks);
		log_action("is sleeping", philo);
		ft_usleep(philo->info.tts, philo);
		log_action("is thinking", philo);
		usleep(500);
	}
}

void	philo_process(t_philo *philo)
{
	if (philo->id % 2)
		usleep(500);
	philo_life(philo);
}

void	start_simulation(t_philo *philos)
{
	pid_t		pid;
	int			i;
	pthread_t	monitor;
	pthread_t	sim_status;

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
			pthread_create(&monitor, NULL, am_alive, &philos[i]);
			pthread_create(&sim_status, NULL, sim_status_func, &philos[i]);
			philo_process(&philos[i]);
			pthread_join(monitor, NULL);
			pthread_join(sim_status, NULL);
		}
		i++;
	}
}

void	init_philos(t_philo *philos, t_info info)
{
	int	i;

	i = 0;
	while (i < info.nbr)
	{
		pthread_mutex_init(&philos[i].mtx, NULL);
		pthread_mutex_init(&philos[i].mtx_sim_status, NULL);
		philos[i].id = i + 1;
		philos[i].info = info;
		philos[i].eat_times = 0;
		philos[i].sim_status = 1;
		i++;
	}
}


void	init_simaphors(t_info *info)
{
	sem_unlink(SEM_FORKS);
	info->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_TRUNC, 0644, info->nbr);
	if (info->sem_forks == SEM_FAILED)
	{
		perror("sem_open_init_semaphore");
		exit(1);
	}
	sem_unlink(SEM_WRITE);
	info->sem_write = sem_open(SEM_WRITE, O_CREAT | O_TRUNC, 0644, 1);
	if (info->sem_write == SEM_FAILED)
	{
		perror("sem_open_init_semaphore");
		exit(1);
	}
	sem_unlink(SEM_SIM_STATUS);
	info->sem_sim_status = sem_open(SEM_SIM_STATUS, O_CREAT | O_TRUNC, 0644, 0);
	if (info->sem_sim_status == SEM_FAILED)
	{
		perror("sem_open_init_semaphore");
		exit(1);
	}
	sem_unlink(SEM_FULL);
	info->sem_full = sem_open(SEM_FULL, O_CREAT | O_TRUNC, 0644, 0);
	if (info->sem_full == SEM_FAILED)
	{
		perror("sem_open_init_semaphore");
		exit(1);
	}
}

void *check_full(void *_philos)
{
	int i;
	t_philo *philos;

	philos = _philos;
	i = philos->info.nbr;
	while (i > 0)
	{
		sem_wait(philos->info.sem_full);
		i--;
	}
	sem_post(philos->info.sem_sim_status);
	sem_post(philos->info.sem_sim_status);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	philos[PHILO_MAX_NUMBER];
	int		status;
	int		i;

	if (ac != 5 && ac != 6)
		return (0);
	t_info info = {
		.nbr = atoi(av[1]),
		.ttd = atoi(av[2]),
		.tte = atoi(av[3]),
		.tts = atoi(av[4]),
	};
	if (ac == 6)
		info.time_of_eats = atoi(av[5]);
	else
		info.time_of_eats = -1;
	init_simaphors(&info);
	init_philos(philos, info);
	start_simulation(philos);
	pthread_t thrd;
	pthread_create(&thrd, NULL, check_full, &philos);
	pthread_detach(thrd);
	i = 0;
	while (i < info.nbr)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	sem_close(info.sem_forks);
	sem_close(info.sem_write);
	sem_close(info.sem_sim_status);
	sem_close(info.sem_full);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_SIM_STATUS);
	sem_unlink(SEM_FULL);
	usleep(500000);
	return (0);
}
