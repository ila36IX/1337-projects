/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:28:11 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 03:52:30 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_collectables(t_game *game)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->map[y][x] == 'C')
				i++;
			x++;
		}
		y++;
	}
	return (i);
}

void	set_exit_pos(t_game *game)
{
	int		x;
	int		y;
	t_pos	e_p;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'E')
			{
				e_p.x = x;
				e_p.y = y;
			}
			x++;
		}
		y++;
	}
	game->exit_pos = e_p;
}

t_game	*init_game(char **map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx_init();
	game->map = map;
	game->map_w = ft_strlen(map[0]);
	while (map[game->map_h])
		(game->map_h)++;
	game->win_h = game->map_h * IMG_SIZE;
	game->win_w = game->map_w * IMG_SIZE;
	game->window = mlx_new_window(game->mlx, game->win_w, game->win_h,
			"so_long");
	game->collects_count = count_collectables(game);
	set_exit_pos(game);
	return (game);
}
