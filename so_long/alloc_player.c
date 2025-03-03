/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:25:15 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 02:34:15 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	**init_player_views(t_game *game)
{
	t_data	**views;

	views = malloc(sizeof(t_data) * VIEWS_END + 1);
	views[LEFT_1] = init_img(game, "./images/banana_left1.xpm");
	views[LEFT_2] = init_img(game, "./images/banana_left2.xpm");
	views[LEFT_3] = init_img(game, "./images/banana_left3.xpm");
	views[RIGHT_1] = init_img(game, "./images/banana_right1.xpm");
	views[RIGHT_2] = init_img(game, "./images/banana_right2.xpm");
	views[RIGHT_3] = init_img(game, "./images/banana_right3.xpm");
	views[TOP_1] = init_img(game, "./images/banana_top1.xpm");
	views[TOP_2] = init_img(game, "./images/banana_top2.xpm");
	views[TOP_3] = init_img(game, "./images/banana_top3.xpm");
	views[BOTTOM_1] = init_img(game, "./images/banana_bottom1.xpm");
	views[BOTTOM_2] = init_img(game, "./images/banana_bottom2.xpm");
	views[BOTTOM_3] = init_img(game, "./images/banana_bottom3.xpm");
	views[STAND_1] = init_img(game, "./images/stand1.xpm");
	views[STAND_2] = init_img(game, "./images/stand2.xpm");
	views[STAND_3] = init_img(game, "./images/stand3.xpm");
	views[VIEWS_END] = NULL;
	return (views);
}

t_pos	*player_position(t_game *game)
{
	t_pos	*pos;
	int		x;
	int		y;

	pos = malloc(sizeof(t_pos));
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->map[y][x] == 'P')
			{
				pos->x = x;
				pos->y = y;
			}
			x++;
		}
		y++;
	}
	return (pos);
}

t_walker	*init_player(t_game *game)
{
	t_walker	*player;

	player = malloc(sizeof(t_walker));
	player->views = init_player_views(game);
	player->off_x = 0;
	player->off_y = 0;
	player->_off_x = 0;
	player->_off_y = 0;
	player->curr = STAND_1;
	player->pos = player_position(game);
	return (player);
}
