/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:58:26 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 02:58:37 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	process_keys_events(t_game *game)
{
	t_walker	*w;

	w = game->assets->player;
	if (w->off_x || w->off_y)
		return ;
	if (game->keycode[KEY_RIGHT])
		walk(game, w, FRAME_RATE, 0);
	else if (game->keycode[KEY_LEFT])
		walk(game, w, -FRAME_RATE, 0);
	else if (game->keycode[KEY_UP])
		walk(game, w, 0, -FRAME_RATE);
	else if (game->keycode[KEY_DOWN])
		walk(game, w, 0, FRAME_RATE);
}

int	release(int keycode, t_game *game)
{
	if (keycode == 100)
		game->keycode[KEY_RIGHT] = 0;
	if (keycode == 97)
		game->keycode[KEY_LEFT] = 0;
	if (keycode == 119)
		game->keycode[KEY_UP] = 0;
	if (keycode == 115)
		game->keycode[KEY_DOWN] = 0;
	return (0);
}

void	reset_kyes(t_game *game)
{
	game->keycode[KEY_RIGHT] = 0;
	game->keycode[KEY_LEFT] = 0;
	game->keycode[KEY_UP] = 0;
	game->keycode[KEY_DOWN] = 0;
}

int	press(int keycode, t_game *game)
{
	t_walker	*w;

	w = game->assets->player;
	if (keycode == 65307)
		quit(game, 0, "Exiting...");
	if (keycode == 100)
		game->keycode[KEY_RIGHT] = 1;
	if (keycode == 97)
		game->keycode[KEY_LEFT] = 1;
	if (keycode == 119)
		game->keycode[KEY_UP] = 1;
	if (keycode == 115)
		game->keycode[KEY_DOWN] = 1;
	return (0);
}
