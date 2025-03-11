/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:38:02 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 03:02:32 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_exit_frame(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'E')
			{
				if (game->collects_count > 0)
					draw_img(game, game->assets->exit_close, x, y);
				else
					draw_img(game, game->assets->exit_open, x, y);
			}
			x++;
		}
		y++;
	}
}

void	render(t_game *game, unsigned int curr_frame)
{
	t_walker	*player;
	int			j;

	j = 0;
	player = game->assets->player;
	if (curr_frame % (BASE / SPEED) == 0)
	{
		while (game->assets->enemies[j])
			check_collision(game, game->assets->player,
				game->assets->enemies[j++]);
		render_exit_frame(game);
		move_enemies(game);
		move_to_next_cell(player);
		draw_walker(game, player);
		rander_steps_counter(game, game->steps);
	}
	if (curr_frame % (((BASE / SPEED) * IMG_SIZE) / FRAMES) == 0)
		set_next_frame_content(game);
}

void	draw_walker(t_game *game, t_walker *charachter)
{
	t_data	*view;
	t_data	*erase;

	view = charachter->views[charachter->curr];
	erase = game->assets->empty;
	mlx_put_image_to_window(game->mlx, game->window, erase, charachter->pos->x
		* IMG_SIZE + charachter->_off_x, charachter->pos->y * IMG_SIZE
		+ charachter->_off_y + HEADER_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, view, charachter->pos->x
		* IMG_SIZE + charachter->off_x, charachter->pos->y * IMG_SIZE
		+ charachter->off_y + HEADER_SIZE);
	charachter->_off_x = charachter->off_x;
	charachter->_off_y = charachter->off_y;
}

void	draw_img(t_game *game, t_data *asset, int pex_x, int pex_y)
{
	int	x;
	int	y;

	x = pex_x * IMG_SIZE;
	y = pex_y * IMG_SIZE;
	mlx_put_image_to_window(game->mlx, game->window, asset, x, y + HEADER_SIZE);
}
