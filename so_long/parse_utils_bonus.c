/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:48:16 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/07 20:50:33 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * free_ids - Free allocated memory for ids of entries in the map
 *
 * @ids: Matrix of ids of every entry in the map
 * @width: map width
 * @height: map height
 *
 * Return: Nothing
 */
void	free_ids(int **ids, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(ids[i++]);
	free(ids);
}

/**
 * get_player_id - get player id which will be compared with collectables ids
 * and exit id
 *
 * @map: Map readded from file, map must contains at least one P character
 * @ids: Matrix of ids of every entry in the map
 * @width: map width
 * @height: map height
 */
int	get_player_id(char **map, int **ids, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'P')
				return (ids[y][x]);
			x++;
		}
		y++;
	}
	return (-1);
}

/**
 * exit_if_not_solvable - Check if all collectables and exit have the some id as
 * player, if not that means map is not solvable and exit will be called
 *
 * @map: valid map readded from the file
 * @ids: Matrix of ids of every entry in the map
 * @width: map width
 * @height: map height
 */
void	exit_if_not_solvable(char **map, int **ids, int width, int height)
{
	int	x;
	int	y;
	int	player_id;

	player_id = get_player_id(map, ids, width, height);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if ((map[y][x] == 'C' || map[y][x] == 'E')
				&& ids[y][x] != player_id)
			{
				free_ids(ids, height);
				map_error_exit(map, "Map not solvable");
			}
			x++;
		}
		y++;
	}
}
