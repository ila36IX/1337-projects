#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


#define TIMEOUT_DELAY 1000000
#define QUEUE_DELAY 50
#define RETRIES 3

int ackn_recieved = 0;

void send_bit(int pid, int sig)
{
	int retries;
	int timeout;
	
	ackn_recieved = 0;
	retries = RETRIES;
	while (retries >= 0)
	{
		kill(pid, sig);
		timeout = TIMEOUT_DELAY;
		while (!ackn_recieved && timeout > 0)
		{
			usleep(QUEUE_DELAY);
			timeout -= QUEUE_DELAY;
		}
		if (ackn_recieved)
			return ;
		printf("No response; Retry: %d/%d\n", RETRIES + 1 - retries, RETRIES);
		retries--;
	}
	printf("\n\nServer is not responding;\n");
	exit(1);
}

void send_char(int c, int pid)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			send_bit(pid, SIGUSR2);
		else
			send_bit(pid, SIGUSR1);
		i--;
	}
}

void stream_string(char *s, int pid)
{
	if (!s)
		return ;
	while (*s)
		send_char(*(s++), pid);
	send_char('\0', pid);
	while (1)
		pause();
}

void handle_ackn(int signo, siginfo_t *info, void *context)
{
	if (signo == SIGUSR1)
		ackn_recieved = 1;
	if (signo == SIGUSR2)
	{
		printf("Server acknowledges\n");
		exit(1);
	}
}

int main(int ac, char **av)
{
	int pid;
	struct sigaction sa = {0};

	sa.sa_sigaction = handle_ackn;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	if (ac != 3)
	{
		printf("Usage: <PID> <message>\n");
		return (1);
	}
	pid = atoi(av[1]);
	if (pid == 0)
	{
		printf("Error: zero or unvalid PID\n");
		return (1);
	}
	printf("%d\n", pid);
	stream_string(av[2], pid);
	return (0);
}

