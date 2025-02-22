/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:48:27 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/08 13:41:54 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void move_dir(t_game *game, int x_offset, int y_offset)
{
	t_pos c;

	c = game->pos;
	if (c.x + x_offset >= game->map_w || c.x + x_offset < 0)
		return ;
	if (c.y + y_offset >= game->map_h || c.y + y_offset < 0)
		return ;
	if (game->map[c.y + y_offset][c.x + x_offset] == '1')
		return ;
	game->map[c.y][c.x] = '0';
	game->map[c.y + y_offset][c.x + x_offset] = 'P';
	(game->pos.x) += x_offset;
	(game->pos.y) += y_offset;
}

void update_pos(t_game *game, char *direction)
{
	t_pos c;

	c = game->pos;
	if (strcmp(direction, "up") == 0)
		move_dir(game, 0, -1);
	else if (strcmp(direction, "down") == 0)
		move_dir(game, 0, 1);
	else if (strcmp(direction, "left") == 0)
		move_dir(game, -1, 0);
	else if (strcmp(direction, "right") == 0)
		move_dir(game, 1, 0);
	game->curr_face = direction;
}
