/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:49:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/21 20:49:23 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	render_next_frame(void *YourStruct);



void swap2d(t_data ***map, t_pos *from, t_pos *to)
{
        t_data *tmp;

        tmp = map[from->x][from->y];
        map[from->x][from->y] = map[to->x][to->y];
        map[from->x][from->y] = tmp;
}

void draw_img(t_game *game, t_data *asset, int pex_x, int pex_y)
{
        int x;
        int y;

        x = pex_x * IMG_SIZE;
        y = pex_y * IMG_SIZE;
        mlx_put_image_to_window(game->mlx, game->window, asset, x, y);
}

void draw(t_game *game)
{
        t_assets *assets;

        assets = game->assets;
        for (int y = 0; y < game->map_h; y++)
        {
                for (int x = 0; x < game->map_w; x++)
                        if (game->map[y][x] == '1')
                                draw_img(game, assets->wall, x, y);
                        else if (game->map[y][x] == 'C')
                                draw_img(game, assets->peel, x, y);
                                /*else if (game->map[y][x] == '0')*/
                                /*	draw_img(game, assets->empty, x, y);*/
                        else if (game->map[y][x] == 'P')
                                draw_img(game, assets->banana, x, y);
        }
}

int f(int key_code, t_game *game)
{
        printf("Press: %d\n", key_code);
        if (key_code == 100)
                update_pos(game, "right");
        if (key_code == 97)
                update_pos(game, "left");
        if (key_code == 119)
                update_pos(game, "up");
        if (key_code == 115)
                update_pos(game, "down");
        mlx_clear_window(game->mlx, game->window);
        draw(game);
        return (0);
}

/*int update(t_game *game)*/
/*{*/
/*	usleep(100000);*/
/*	return (0);*/
/*}*/

int	main(void)
{
        t_game *game;
        t_assets *assets;
        char *map[100] = {
                strdup("11111111111110000000000011"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000P00001"),
                strdup("10000000000000000000C00001"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000000001"),
                strdup("11111011111111111110111111"),
                strdup("10000000000010000000000000"),
                strdup("10000000000010000000C00000"),
                strdup("10000000000010000000000000"),
                strdup("10000000000000000000C00000"),
                strdup("10000000000010000000000000"),
                strdup("10000000000010000000000001"),
                strdup("11000000000011111111111111"),
        };

        game = init_game((char **) map);
        assets = init_assets(game);
        game->assets = assets;
        draw(game);
        mlx_key_hook(game->window, f, game);
        // mlx_loop_hook(game->mlx, update, game);
       mlx_loop(game->mlx);
        return (0);
}

