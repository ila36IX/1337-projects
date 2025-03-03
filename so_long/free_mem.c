/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:55:37 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 03:23:32 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_dynamic_charachter(t_game *game, t_walker *c)
{
	int	i;

	i = 0;
	while (i < VIEWS_END)
		mlx_destroy_image(game->mlx, c->views[i++]);
	free(c->pos);
	free(c->views);
	free(c);
}

void	free_game_assets(t_game *game)
{
	int	i;

	mlx_destroy_image(game->mlx, game->assets->background);
	mlx_destroy_image(game->mlx, game->assets->wall);
	mlx_destroy_image(game->mlx, game->assets->empty);
	mlx_destroy_image(game->mlx, game->assets->peel);
	mlx_destroy_image(game->mlx, game->assets->header);
	mlx_destroy_image(game->mlx, game->assets->header_counter);
	mlx_destroy_image(game->mlx, game->assets->exit_close);
	mlx_destroy_image(game->mlx, game->assets->exit_open);
	i = 0;
	while (i <= 9)
		mlx_destroy_image(game->mlx, game->assets->numbers[i++]);
	free(game->assets->numbers);
	free_dynamic_charachter(game, game->assets->player);
	i = 0;
	while (game->assets->enemies[i])
		free_dynamic_charachter(game, game->assets->enemies[i++]);
	free(game->assets->enemies);
	free(game->assets);
}

void	clear_game(t_game *game)
{
	free_game_assets(game);
	free_map(game->map);
	free(game->keycode);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

void	quit(t_game *game, int exit_code, char *message)
{
	printf("%s\n", message);
	clear_game(game);
	exit(exit_code);
}
