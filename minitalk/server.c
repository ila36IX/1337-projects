#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

/*
 * 0xxxxxxx
 * 110xxxxx 10xxxxxx
 * 1110xxxx 10xxxxxx 10xxxxxx
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 **/

typedef struct shared_data {
	char *s;
	int byte_i;
	int bit_i;
	int sender_pid;
} t_stream;

t_stream *payload = NULL;

#define BYTE_INDEX (payload->byte_i)
#define BIT_INDEX (payload->bit_i)
#define CURR_CHAR ((payload->s)[payload->byte_i])
#define STREAM (payload->s)
#define BUFFER_SIZE 9

void next_byte()
{
	BIT_INDEX = 0;
	if (!CURR_CHAR)
	{
		printf("%s", STREAM);
		BYTE_INDEX = 0;
		bzero(STREAM, BUFFER_SIZE);
		kill(payload->sender_pid, SIGUSR2);
		return ;
	}
	BYTE_INDEX++;
	if (BYTE_INDEX % (BUFFER_SIZE - 1) == 0)
	{
		printf("%s", STREAM);
		bzero(STREAM, BUFFER_SIZE);
		BYTE_INDEX = 0;
	}
}

void	process_bit(char bit)
{
	CURR_CHAR = (CURR_CHAR << 1) | bit;
	if (BIT_INDEX == 7)
		next_byte();
	else
		BIT_INDEX++;
}

void handle_bit(int signo, siginfo_t *info, void *context) 
{
	pid_t sender_pid;

	sender_pid = info->si_pid;
	payload->sender_pid = sender_pid;
	process_bit(signo == SIGUSR2);
	kill(sender_pid, SIGUSR1);
}

int main()
{
	pid_t	pid;
	t_stream s = {0};
	struct sigaction sa = {0};

	payload = &s;
	sa.sa_sigaction = handle_bit;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pid = getpid();
	printf("PID [%d]\n", pid);
	STREAM = calloc(BUFFER_SIZE, sizeof(char));
	while (1)
		pause();
	return (0);
}

