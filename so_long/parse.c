/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:15:32 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/10 21:44:26 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_surrounded_by_walls(char **map)
{
	size_t	rows;
	size_t	cols;
	size_t	i;

	rows = 0;
	while (map[rows])
		rows++;
	cols = ft_strlen(map[0]);
	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			map_error_exit(map, "Map must be surrounded by walls");
		i++;
	}
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			map_error_exit(map, "Map must be surrounded by walls");
		i++;
	}
}

void	check_map_rectangularly(char **map)
{
	size_t	i;
	size_t	width;

	width = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i++]) != width)
			map_error_exit(map, "All lines must have the same width");
	}
}

void	count_charachters(char **map, unsigned int *counters, char c)
{
	if (c == '0')
		counters[0]++;
	else if (c == '1')
		counters[1]++;
	else if (c == 'C')
		counters[2]++;
	else if (c == 'E')
		counters[3]++;
	else if (c == 'P')
		counters[4]++;
	else
		map_error_exit(map, "Unknown characher in the giving map");
	if (counters[3] > 1)
		map_error_exit(map, "Duplicate exit in the giving map");
	if (counters[4] > 1)
		map_error_exit(map, "Duplicate starting position in the giving map");
}

void	check_charachters(char **map)
{
	int				i;
	int				j;
	unsigned int	counters[7];

	i = 0;
	ft_bzero(&counters, sizeof(int) * 7);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			count_charachters(map, counters, map[i][j++]);
		i++;
	}
	if (counters[2] == 0)
		map_error_exit(map, "No collectibles in the giving map");
	if (counters[3] == 0)
		map_error_exit(map, "No exit in the giving map");
	if (counters[4] == 0)
		map_error_exit(map, "No starting position in the giving map");
}

void	map_checker(char **map)
{
	check_charachters(map);
	check_map_rectangularly(map);
	check_map_surrounded_by_walls(map);
	check_map_solveability(map);
}
