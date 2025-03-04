/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:55:18 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/04 00:55:34 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error_exit(char **map, char *error)
{
	free_map(map);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

void	sys_error_exit(char *prefix)
{
	ft_putendl_fd("Error", 2);
	perror(prefix);
	exit(EXIT_FAILURE);
}
