/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:25:15 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/09 21:04:53 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	**init_player_views(t_game *game)
{
	t_data	**views;

	views = ft_calloc(VIEWS_END + 1, sizeof(t_data));
	views[LEFT_1] = init_img(game, "./textures/banana_left1.xpm");
	views[LEFT_2] = init_img(game, "./textures/banana_left2.xpm");
	views[LEFT_3] = init_img(game, "./textures/banana_left3.xpm");
	views[RIGHT_1] = init_img(game, "./textures/banana_right1.xpm");
	views[RIGHT_2] = init_img(game, "./textures/banana_right2.xpm");
	views[RIGHT_3] = init_img(game, "./textures/banana_right3.xpm");
	views[TOP_1] = init_img(game, "./textures/banana_top1.xpm");
	views[TOP_2] = init_img(game, "./textures/banana_top2.xpm");
	views[TOP_3] = init_img(game, "./textures/banana_top3.xpm");
	views[BOTTOM_1] = init_img(game, "./textures/banana_bottom1.xpm");
	views[BOTTOM_2] = init_img(game, "./textures/banana_bottom2.xpm");
	views[BOTTOM_3] = init_img(game, "./textures/banana_bottom3.xpm");
	views[STAND_1] = init_img(game, "./textures/stand1.xpm");
	views[STAND_2] = init_img(game, "./textures/stand2.xpm");
	views[STAND_3] = init_img(game, "./textures/stand3.xpm");
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
