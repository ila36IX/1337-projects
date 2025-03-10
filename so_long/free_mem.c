/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:55:37 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 03:51:20 by aljbari          ###   ########.fr       */
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

void	free_dynamic_charachter(t_walker *c)
{
	free(c->pos);
	free(c->view);
	free(c);
}

void	free_game_assets(t_game *game)
{
	mlx_destroy_image(game->mlx, game->assets->background);
	mlx_destroy_image(game->mlx, game->assets->wall);
	mlx_destroy_image(game->mlx, game->assets->empty);
	mlx_destroy_image(game->mlx, game->assets->peel);
	mlx_destroy_image(game->mlx, game->assets->exit_close);
	mlx_destroy_image(game->mlx, game->assets->exit_open);
	free_dynamic_charachter(game->assets->player);
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
	ft_printf("%s\n", message);
	clear_game(game);
	exit(exit_code);
}
