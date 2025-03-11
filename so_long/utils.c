/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:59:07 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/09 20:59:21 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
