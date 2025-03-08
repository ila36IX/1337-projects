/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:22:34 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 02:27:38 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	**init_enemy_views(t_game *game)
{
	t_data	**views;

	views = ft_calloc(VIEWS_END + 1, sizeof(t_data));
	views[LEFT_1] = init_img(game, "./images/monster_left1.xpm");
	views[LEFT_2] = init_img(game, "./images/monster_left2.xpm");
	views[LEFT_3] = init_img(game, "./images/monster_left3.xpm");
	views[RIGHT_1] = init_img(game, "./images/monster_right1.xpm");
	views[RIGHT_2] = init_img(game, "./images/monster_right2.xpm");
	views[RIGHT_3] = init_img(game, "./images/monster_right1.xpm");
	views[TOP_1] = init_img(game, "./images/monster_up1.xpm");
	views[TOP_2] = init_img(game, "./images/monster_up2.xpm");
	views[TOP_3] = init_img(game, "./images/monster_up3.xpm");
	views[BOTTOM_1] = init_img(game, "./images/monster_down1.xpm");
	views[BOTTOM_2] = init_img(game, "./images/monster_down2.xpm");
	views[BOTTOM_3] = init_img(game, "./images/monster_down3.xpm");
	views[STAND_1] = init_img(game, "./images/monster_right1.xpm");
	views[STAND_2] = init_img(game, "./images/monster_right2.xpm");
	views[STAND_3] = init_img(game, "./images/monster_right3.xpm");
	views[VIEWS_END] = NULL;
	return (views);
}

t_walker	*init_enemy(t_game *game, int x, int y)
{
	t_walker	*enemy;

	enemy = malloc(sizeof(t_walker));
	enemy->views = init_enemy_views(game);
	enemy->off_x = 0;
	enemy->off_y = 0;
	enemy->_off_x = 0;
	enemy->_off_y = 0;
	enemy->curr = STAND_1;
	enemy->pos = malloc(sizeof(t_pos));
	enemy->pos->x = x;
	enemy->pos->y = y;
	enemy->direction = DIRECTION_LEFT;
	return (enemy);
}

int	count_enemies(t_game *game)
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
			if (game->map[y][x] == 'M')
				i++;
			x++;
		}
		y++;
	}
	return (i);
}

t_walker	**init_enemies(t_game *game)
{
	t_walker	**enemies;
	int			i;
	int			x;
	int			y;

	enemies = ft_calloc(count_enemies(game) + 1, sizeof(t_walker));
	y = 0;
	i = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->map[y][x] == 'M')
			{
				enemies[i++] = init_enemy(game, x, y);
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (enemies);
}
