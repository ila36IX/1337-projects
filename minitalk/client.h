/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:59:25 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/14 10:03:54 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define TIMEOUT_DELAY 1000000
# define QUEUE_DELAY 50
# define RETRIES 3

unsigned int	ft_atol_parse(char *s);

#endif
