/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:49:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/02 18:21:03 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <time.h>


void quit(t_game *game)
{
        clear_game(game);
        exit(0);
}

void debug(t_game *game, unsigned int i)
{
        printf("%10s: (%d, %d)\n", "GRID", game->assets->player->pos->x,
               game->assets->player->pos->y);
        printf("%10s: (%d, %d)\n", "OFFSET", game->assets->player->off_x,
               game->assets->player->off_y);
        printf("%10s: (%d, %d)\n", "_OFFSET", game->assets->player->_off_x,
               game->assets->player->_off_y);
        printf("%10s: ", "INPUTS");
        printf("%s", game->keycode[KEY_RIGHT] ? "🠲  " : "");
        printf("%s", game->keycode[KEY_LEFT] ? "🠰  " : "");
        printf("%s", game->keycode[KEY_UP] ? "🠱 " : "");
        printf("%s", game->keycode[KEY_DOWN] ? "🠯 " : "");
        printf("%10s: %d\n", "Peels number", game->collects_count);
        printf("\n");

        /* Sepirator */
        printf("\n");
}

int abs(int n)
{
        if (n < 0)
                return (n * -1);
        else
                return (n);
}

int _update(t_game *game)
{
        static unsigned int curr_frame;

        curr_frame++;
        process_keys_events(game);
        render(game, curr_frame);
        usleep(2000);
        debug(game, curr_frame);
        return (0);
}

void    start_game(char **map)
{
        t_game *game;

        game = init_game((char **) map);
        game->assets = init_assets(game);;
        // update later that background is not big enough to fit in all sizes
        draw(game);
        mlx_loop_hook(game->mlx, _update, game);
        // press and relase key events handlers
        mlx_hook(game->window, 2, 1L<<0, press, game);
        mlx_hook(game->window, 3, 1L<<1, release, game);
        mlx_loop(game->mlx);
}

int	main(void)
{
        char *map[100] = {
                strdup("11111111111111111111111111"),
                strdup("1P000000000000000000C00001"),
                strdup("1000000E000000000000C00001"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000000001"),
                strdup("11111011111111111110111111"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000C00001"),
                strdup("10000000000010000000000001"),
                strdup("100M0000000000000000C00001"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000000001"),
                strdup("11111111111111111111111111"),
                NULL
        };
        start_game(map);
        return (0);
}
