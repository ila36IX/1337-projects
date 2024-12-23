#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
/*
 * 0xxxxxxx
 * 110xxxxx 10xxxxxx
 * 1110xxxx 10xxxxxx 10xxxxxx
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 * */

struct shared_data {
	char o;
	int n;
};

struct shared_data *shared_mem = NULL;


void handle_siguser1(int n)
{
	shared_mem->o = (shared_mem->o << 1) | 0;
	(shared_mem->n)++;
	if (shared_mem->n == 8)
	{
		printf("%c", shared_mem->o);
		shared_mem->n = 0;
	}
}

void handle_siguser2(int n)
{ 
	shared_mem->o = (shared_mem->o << 1) | 1;
	(shared_mem->n)++;
	if (shared_mem->n == 8)
	{
		printf("%c", shared_mem->o);
		shared_mem->n = 0;
	}
}

int main()
{
	int pid;
	struct sigaction sa1 = {0};
	struct sigaction sa2 = {0};
	struct shared_data s = {0};

	sa1.sa_handler = handle_siguser1;
	sigaction(SIGUSR1, &sa1, NULL);

	sa2.sa_handler = handle_siguser2;
	sigaction(SIGUSR2, &sa2, NULL);

	shared_mem = &s;
	pid = getpid();
	printf("PID [%d]\n", pid);
	while (1)
	{
		pause();
	}
	return (0);
}

