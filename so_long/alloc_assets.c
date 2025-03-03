/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:30:48 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 02:50:09 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	**init_numbers_assets(t_game *game)
{
	t_data	**numbers;

	numbers = malloc(sizeof(t_data) * 10);
	numbers[0] = init_img(game, "./images/digit0.xpm");
	numbers[1] = init_img(game, "./images/digit1.xpm");
	numbers[2] = init_img(game, "./images/digit2.xpm");
	numbers[3] = init_img(game, "./images/digit3.xpm");
	numbers[4] = init_img(game, "./images/digit4.xpm");
	numbers[5] = init_img(game, "./images/digit5.xpm");
	numbers[6] = init_img(game, "./images/digit6.xpm");
	numbers[8] = init_img(game, "./images/digit8.xpm");
	numbers[7] = init_img(game, "./images/digit7.xpm");
	numbers[9] = init_img(game, "./images/digit9.xpm");
	return (numbers);
}

t_assets	*init_assets(t_game *game)
{
	t_assets	*assets;

	assets = malloc(sizeof(t_assets));
	assets->wall = init_img(game, "./images/wall.xpm");
	assets->peel = init_img(game, "./images/peel.xpm");
	assets->empty = init_img(game, "./images/empty.xpm");
	assets->background = init_img(game, "./images/background.xpm");
	assets->exit_close = init_img(game, "./images/trash_closed.xpm");
	assets->exit_open = init_img(game, "./images/trash_open.xpm");
	assets->header_counter = init_img(game,
			"./images/banner_with_steps_counter.xpm");
	assets->header = init_img(game, "./images/banner.xpm");
	assets->player = init_player(game);
	assets->enemies = init_enemies(game);
	assets->numbers = init_numbers_assets(game);
	game->keycode = malloc(sizeof(int) * 4);
	game->keycode[0] = 0;
	game->keycode[1] = 0;
	game->keycode[2] = 0;
	game->keycode[3] = 0;
	game->speed = 0;
	game->frames = 0;
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
		printf("Img init Error: \"%s\" exists?\n", path);
	return (img);
}
