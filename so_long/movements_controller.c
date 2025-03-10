/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:25:42 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/10 21:27:59 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_dir(t_game *game, int x_offset, int y_offset)
{
	t_pos	*c;

	c = game->assets->player->pos;
	if (c->x + x_offset >= game->map_w || c->x + x_offset < 0)
		return ;
	if (c->y + y_offset >= game->map_h || c->y + y_offset < 0)
		return ;
	if (game->map[c->y + y_offset][c->x + x_offset] == '1')
		return ;
	if (game->map[c->y + y_offset][c->x + x_offset] == 'C')
		game->collects_count--;
	if (game->map[c->y + y_offset][c->x + x_offset] == 'E'
		&& !game->collects_count)
		quit(game, 0, "You win!");
	game->steps++;
	ft_printf("number of movements: %d\n", game->steps);
	game->map[c->y][c->x] = '0';
	game->map[c->y + y_offset][c->x + x_offset] = 'P';
	(game->assets->player->pos->x) += x_offset;
	(game->assets->player->pos->y) += y_offset;
}

void	update_pos(t_game *game, char *direction)
{
	if (ft_strncmp(direction, "up", 2) == 0)
		move_dir(game, 0, -1);
	else if (ft_strncmp(direction, "down", 4) == 0)
		move_dir(game, 0, 1);
	else if (ft_strncmp(direction, "left", 4) == 0)
		move_dir(game, -1, 0);
	else if (ft_strncmp(direction, "right", 5) == 0)
		move_dir(game, 1, 0);
}

int	press_handler(int key_code, t_game *game)
{
	if (key_code == 100)
		update_pos(game, "right");
	if (key_code == 97)
		update_pos(game, "left");
	if (key_code == 119)
		update_pos(game, "up");
	if (key_code == 115)
		update_pos(game, "down");
	if (key_code == 65307)
		quit(game, 0, "Exiting...");
	mlx_clear_window(game->mlx, game->window);
	draw(game);
	return (0);
}
