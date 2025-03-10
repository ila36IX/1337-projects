/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:30:48 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/09 21:05:10 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	player->view = init_img(game, "./textures/stand2.xpm");
	player->pos = player_position(game);
	return (player);
}

t_assets	*init_assets(t_game *game)
{
	t_assets	*assets;

	assets = malloc(sizeof(t_assets));
	assets->wall = init_img(game, "./textures/wall.xpm");
	assets->peel = init_img(game, "./textures/peel.xpm");
	assets->empty = init_img(game, "./textures/empty.xpm");
	assets->background = init_img(game, "./textures/background.xpm");
	assets->exit_open = init_img(game, "./textures/exit_open.xpm");
	assets->exit_close = init_img(game, "./textures/exit_close.xpm");
	assets->player = init_player(game);
	game->steps = 0;
	return (assets);
}

void	*init_img(t_game *game, char *path)
{
	int		w;
	int		h;
	void	*img;

	img = NULL;
	img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!img)
		ft_printf("Img init Error: \"%s\" exists?\n", path);
	return (img);
}
