/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:49:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/04 00:59:04 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*void	debug(t_game *game)*/
/*{*/
/*	printf("%10s: (%d, %d)\n", "GRID", game->assets->player->pos->x,*/
/*		game->assets->player->pos->y);*/
/*	printf("%10s: (%d, %d)\n", "OFFSET", game->assets->player->off_x,*/
/*		game->assets->player->off_y);*/
/*	printf("%10s: (%d, %d)\n", "_OFFSET", game->assets->player->_off_x,*/
/*		game->assets->player->_off_y);*/
/*	printf("%10s: ", "INPUTS");*/
/*	printf("%s", game->keycode[KEY_RIGHT] ? "🠲  " : "");*/
/*	printf("%s", game->keycode[KEY_LEFT] ? "🠰  " : "");*/
/*	printf("%s", game->keycode[KEY_UP] ? "🠱 " : "");*/
/*	printf("%s", game->keycode[KEY_DOWN] ? "🠯 " : "");*/
/*	printf("%10s: %d\n", "Peels number", game->collects_count);*/
/*	printf("\n");*/
/*	printf("\n");*/
/*}*/

int	abs(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}

int	update(t_game *game)
{
	static unsigned int	curr_frame;

	curr_frame++;
	process_keys_events(game);
	render(game, curr_frame);
	usleep(2000);
	return (0);
}

void	start_game(char **map)
{
	t_game	*game;

	game = init_game((char **)map);
	game->assets = init_assets(game);
	draw_static_objects(game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_hook(game->window, 2, 1L << 0, press, game);
	mlx_hook(game->window, 3, 1L << 1, release, game);
	mlx_loop(game->mlx);
}

void	map_limit_exit(char **map)
{
	int	width;
	int	height;

	width = ft_strlen(map[0]);
	height = 0;
	while (map[height])
		height++;
	if (width * IMG_SIZE > MAX_WINDOW_WIDTH || height
		* IMG_SIZE > MAX_WINDOW_HEIGHT - IMG_SIZE * 2)
	{
		ft_printf("Map is solvable, but...\n");
		map_error_exit(map, "Window size is bigger than the limit");
	}
}

int	main(int ac, char *av[])
{
	char	**map;

	if (ac != 2)
	{
		ft_printf("Usage: %s path/to/map.ber\n", av[0]);
		return (0);
	}
	map = read_map(av[1]);
	map_limit_exit(map);
	start_game(map);
	return (0);
}
