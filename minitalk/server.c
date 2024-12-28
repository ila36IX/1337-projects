/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:04:41 by aljbari           #+#    #+#             */
/*   Updated: 2024/12/28 14:43:18 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
 * 0xxxxxxx
 * 110xxxxx 10xxxxxx
 * 1110xxxx 10xxxxxx 10xxxxxx
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 **/

t_stream	*g_payload;

void	next_byte(void)
{
	char	curr_char;

	curr_char = (g_payload->s)[g_payload->byte_i];
	g_payload->bit_i = 0;
	if (!curr_char)
	{
		ft_printf("%s\n", g_payload->s);
		g_payload->byte_i = 0;
		ft_bzero(g_payload->s, BUFFER_SIZE);
		kill(g_payload->sender_pid, SIGUSR2);
		return ;
	}
	(g_payload->byte_i)++;
	if (g_payload->byte_i % (BUFFER_SIZE - 1) == 0)
	{
		ft_printf("%s", g_payload->s);
		ft_bzero(g_payload->s, BUFFER_SIZE);
		g_payload->byte_i = 0;
	}
}

void	process_bit(char bit)
{
	char	curr_char;

	curr_char = (g_payload->s)[g_payload->byte_i];
	(g_payload->s)[g_payload->byte_i] = (curr_char << 1) | bit;
	if (g_payload->bit_i == 7)
		next_byte();
	else
		(g_payload->bit_i)++;
}

void	handle_bit(int signo, siginfo_t *info, void *context)
{
	pid_t	sender_pid;

	(void)context;
	sender_pid = info->si_pid;
	g_payload->sender_pid = sender_pid;
	process_bit(signo == SIGUSR2);
	kill(sender_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	t_stream			s;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	ft_bzero(&s, sizeof(s));
	g_payload = &s;
	sa.sa_sigaction = handle_bit;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("PID [%d]\n", pid);
	g_payload->s = ft_calloc(BUFFER_SIZE, sizeof(char));
	while (1)
		pause();
	return (0);
}
