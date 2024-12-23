#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


#define QUEUE_DELAY 200
#ifndef SERVER_PID
	#define SERVER_PID 19271
#endif


void send_char(int c, int pid)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			usleep(QUEUE_DELAY);
			kill(pid, SIGUSR2);
		}
		else
	{
			usleep(QUEUE_DELAY);
			kill(pid, SIGUSR1);
		}
		i--;
	}
}

void stream_string(char *s, int pid)
{
	if (!s)
		return ;
	while (*s)
	{
		send_char(*s, SERVER_PID);
		s++;
	}
}

int main(int ac, char **av)
{
	stream_string("tesing is everyhting Explanation of Changes Static Buffer: Instead of an array of buffers (buffer[1024]), a single static .\n", SERVER_PID);
	return (0);
}

