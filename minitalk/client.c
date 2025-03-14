/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:59:36 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/14 10:05:57 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		g_ackn_recieved = 0;

void	send_bit(int pid, int sig)
{
	int	retries;
	int	timeout;

	g_ackn_recieved = 0;
	retries = RETRIES;
	while (retries >= 0)
	{
		kill(pid, sig);
		timeout = TIMEOUT_DELAY;
		while (!g_ackn_recieved && timeout > 0)
		{
			usleep(QUEUE_DELAY);
			timeout -= QUEUE_DELAY;
		}
		if (g_ackn_recieved)
			return ;
		ft_printf("Retry: %d/%d\n", RETRIES + 1 - retries, RETRIES);
		retries--;
	}
	ft_printf("\n\nServer is not responding;\n");
	exit(1);
}

void	send_char(int c, int pid)
{
	int	i;

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

void	stream_string(char *s, int pid)
{
	if (!s)
		return ;
	while (*s)
		send_char(*(s++), pid);
	send_char('\0', pid);
	while (1)
		pause();
}

void	handle_ackn(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signo == SIGUSR1)
		g_ackn_recieved = 1;
	if (signo == SIGUSR2)
	{
		ft_printf("Server acknowledges\n");
		exit(0);
	}
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = handle_ackn;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (ac != 3)
	{
		ft_printf("Usage: <PID> <message>\n");
		return (1);
	}
	pid = ft_atol_parse(av[1]);
	if (pid == 0 || pid == INT_MAX)
	{
		ft_printf("Error: unvalid PID\n");
		return (1);
	}
	stream_string(av[2], pid);
	return (0);
}
