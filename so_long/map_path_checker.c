/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 01:46:02 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/09 21:00:50 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * replace_id - Merge (union) two groups after finding common points
 *
 * @ids: Matrix of ids representing group of entries that could be traversed
 * @old: First group id (will be replaced)
 * @new: second group id which will represent connected entries
 *
 * Return: Nothing
 */
void	union_groups(char **map, int **ids, int old, int new)
{
	int	x;
	int	y;
	int	width;
	int	height;

	width = ft_strlen(map[0]);
	height = 0;
	while (map[height])
		height++;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (ids[y][x] == old)
				ids[y][x] = new;
			x++;
		}
		y++;
	}
}

void	quick_find_hlper(int **ids, int x, int y, int *id)
{
	if (y > 1 && ids[y - 1][x] > 0)
		ids[y][x] = ids[y - 1][x];
	else if (x > 1 && ids[y][x - 1] > 0)
		ids[y][x] = ids[y][x - 1];
	else
		ids[y][x] = ++(*id);
}

/**
 * quick_find - Use quick find algorithm to check if player and all collectables
 * and exit are connected, if no connection exit will be called
 *
 * @map: map readded from file
 * @ids: matrix of integers representing map's entries
 * @width: map width
 * @height: map height
 *
 * Return: Nothing, the function exits if it doesn't found a connection
 */
void	quick_find(char **map, int **ids, int width, int height)
{
	int (x), (y), (id);
	id = 1;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == '1' || map[y][x] == 'M')
				ids[y][x] = -1;
			else if (y > 1 && ids[y - 1][x] > 0 && x > 1 && ids[y][x - 1] > 0
				&& ids[y - 1][x] != ids[y][x - 1])
			{
				ids[y][x] = ids[y - 1][x];
				union_groups(map, ids, ids[y][x - 1], ids[y - 1][x]);
			}
			else
				quick_find_hlper(ids, x, y, &id);
			x++;
		}
		y++;
	}
	exit_if_not_solvable(map, ids, width, height);
}

/**
 * check_map_solveability - allocate ids and call quick find algorithm
 *
 * @map: map readded from file
 *
 * Return: nothing, quick_find will exit if no path found
 */
void	check_map_solveability(char **map)
{
	int	**ids;
	int	x;
	int	y;
	int	i;

	x = ft_strlen(map[0]);
	y = 0;
	while (map[y])
		y++;
	ids = ft_calloc(y, sizeof(int *));
	i = 0;
	while (i < y)
		ids[i++] = ft_calloc(x, sizeof(int));
	quick_find(map, ids, x, y);
	free_ids(ids, y);
}

/*static void	print_ids(int **combs, int width, int height)*/
/*{*/
/*	int	x;*/
/*	int	y;*/
/**/
/*	y = 0;*/
/*	while (y < height)*/
/*	{*/
/*		x = 0;*/
/*		while (x < width)*/
/*		{*/
/*			if (combs[y][x] > 0)*/
/*				ft_printf("\e[%dm%2d\e[0m ", combs[y][x] + 26, combs[y][x]);*/
/*			else*/
/*				ft_printf("%2d ", combs[y][x]);*/
/*			x++;*/
/*		}*/
/*		ft_printf("\n");*/
/*		y++;*/
/*	}*/
/*}*/
