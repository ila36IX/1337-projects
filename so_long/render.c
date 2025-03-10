/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:22:46 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/10 21:24:48 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_img(t_game *game, t_data *asset, int pex_x, int pex_y)
{
	int	x;
	int	y;

	x = pex_x * IMG_SIZE;
	y = pex_y * IMG_SIZE;
	mlx_put_image_to_window(game->mlx, game->window, asset, x, y);
}

void	draw_single_map_asset(t_game *game, int x, int y)
{
	t_assets	*assets;

	assets = game->assets;
	if (game->map[y][x] == '1')
		draw_img(game, assets->wall, x, y);
	else if (game->map[y][x] == 'C')
		draw_img(game, assets->peel, x, y);
	else if (game->map[y][x] == '0')
		draw_img(game, assets->empty, x, y);
	else if (game->map[y][x] == 'E')
		draw_img(game, assets->exit_close, x, y);
	else if (game->map[y][x] == 'P')
		draw_img(game, assets->player->view, x, y);
}

void	draw(t_game *game)
{
	t_assets	*assets;
	int			x;
	int			y;

	assets = game->assets;
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
			draw_single_map_asset(game, x++, y);
		y++;
	}
	if (game->map[game->exit_pos.y][game->exit_pos.x] != 'P')
		game->map[game->exit_pos.y][game->exit_pos.x] = 'E';
	draw_img(game, assets->exit_close, game->exit_pos.x, game->exit_pos.y);
	draw_img(game, assets->player->view, assets->player->pos->x,
		assets->player->pos->y);
}
