/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:04:49 by aljbari           #+#    #+#             */
/*   Updated: 2024/12/25 19:55:38 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct shared_data
{
	char	*s;
	int		byte_i;
	int		bit_i;
	int		sender_pid;
}			t_stream;

#define BUFFER_SIZE 1024
