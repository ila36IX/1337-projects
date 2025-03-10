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

t_game	*init_game(char **map)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = mlx_init();
	game->map = map;
	game->map_w = ft_strlen(map[0]);
	while (map[game->map_h])
		(game->map_h)++;
	game->win_h = game->map_h * IMG_SIZE + HEADER_SIZE;
	game->win_w = game->map_w * IMG_SIZE;
	if (game->win_w <= 4 * 64)
		game->win_w = 5 * 64;
	game->window = mlx_new_window(game->mlx, game->win_w, game->win_h,
			"so_long");
	game->collects_count = count_collectables(game);
	return (game);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
