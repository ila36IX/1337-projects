/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:49:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/10 21:28:06 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	destroy(t_game *game)
{
	clear_game(game);
	exit(EXIT_SUCCESS);
}

void	start_game(char **map)
{
	t_game	*game;

	game = init_game((char **)map);
	game->assets = init_assets(game);
	draw(game);
	mlx_key_hook(game->window, press_handler, game);
	mlx_hook(game->window, 17, 0, destroy, game);
	mlx_loop(game->mlx);
}

/**
 * map_limit_exit - Exit if window size is bigger than the screen
 *
 * @map: map of charachters readded from file
 * Return: nothing, function will exit if window limit detected
 */
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
