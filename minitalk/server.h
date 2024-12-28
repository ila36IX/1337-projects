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

#ifndef SERVER_H
# define SERVER_H

# include "libft/libft.h"
# include <signal.h>

typedef struct shared_data
{
	char	*s;
	int		byte_i;
	int		bit_i;
	int		sender_pid;
}			t_stream;

# define BUFFER_SIZE 1024

#endif
