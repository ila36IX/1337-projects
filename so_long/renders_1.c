/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:01:59 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 03:02:27 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_header(t_game *game)
{
	int	x;

	x = 600;
	mlx_put_image_to_window(game->mlx, game->window,
		game->assets->header_counter, 0, 0);
	while (x < game->win_w)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->assets->header,
			x, 0);
		x += 600;
	}
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			mlx_put_image_to_window(game->mlx, game->window,
				game->assets->background, x, y);
			x += 1920;
		}
		y += 1080;
	}
}

void	draw_static_objects(t_game *game)
{
	t_assets	*assets;
	int			y;
	int			x;

	assets = game->assets;
	draw_background(game);
	draw_header(game);
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->map[y][x] == '1')
				draw_img(game, assets->wall, x, y);
			else if (game->map[y][x] == 'C')
				draw_img(game, assets->peel, x, y);
			else if (game->map[y][x] == 'P')
				draw_img(game, assets->player->views[STAND_1], x, y);
			else if (game->map[y][x] == 'E')
				draw_img(game, assets->exit_close, x, y);
			x++;
		}
		y++;
	}
}

void	rander_steps_counter(t_game *game, int steps)
{
	mlx_put_image_to_window(game->mlx, game->window,
		game->assets->numbers[(steps / 1000) % 10], 264 - 40 * 3, 30);
	mlx_put_image_to_window(game->mlx, game->window,
		game->assets->numbers[(steps / 100) % 10], 264 - 40 * 2, 30);
	mlx_put_image_to_window(game->mlx, game->window,
		game->assets->numbers[(steps / 10) % 10], 264 - 40, 30);
	mlx_put_image_to_window(game->mlx, game->window, game->assets->numbers[steps
		% 10], 264, 30);
}
