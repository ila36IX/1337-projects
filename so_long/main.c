/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:49:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/22 21:25:58 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int	render_next_frame(void *YourStruct);

void draw_img(t_game *game, t_data *asset, int pex_x, int pex_y)
{
        int x;
        int y;

        x = pex_x * IMG_SIZE;
        y = pex_y * IMG_SIZE;
        mlx_put_image_to_window(game->mlx, game->window, asset, x, y);
}

void walk(t_game *game, void *object)
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
                        else if (game->map[y][x] == 'P')
                                draw_img(game, assets->banana, x, y);
        }
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
                        else if (game->map[y][x] == 'P')
                                draw_img(game, assets->banana, x, y);
        }
}

int	press(int keycode, t_game *game)
{
        if (keycode == 65307)
        {
                mlx_loop_end (game->mlx);
                mlx_destroy_window(game->mlx, game->window);
                exit(0);
        }
        if (game->assets->player.off_x || game->assets->player.off_y)
                return (0);
        if (keycode == 100 && !game->assets->player.off_x)
                game->assets->player.off_x = 2;
        if (keycode == 97 && !game->assets->player.off_y)
                game->assets->player.off_x = -2;
        if (keycode == 119 && !game->assets->player.off_x)
                game->assets->player.off_y = -2;
        if (keycode == 115 && !game->assets->player.off_x)
                game->assets->player.off_y = 2;

        /*printf("Pressed\n");*/
        printf("KEY: %d\n", keycode);
        return (0);
}

int many;

void    handle_moves(t_game *game, t_moving_asset *p)
{
        if (p->off_x > 0)
        {
                if (p->curr == RIGHT_1)
                        p->curr = RIGHT_2;
                else if (p->curr == RIGHT_2)
                        p->curr = RIGHT_3;
                else
                        p->curr = RIGHT_1;
                move_right(&game->pos, p);
        }
        else if (p->off_x < 0)
        {
                if (p->curr == LEFT_1)
                        p->curr = LEFT_2;
                else if (p->curr == LEFT_2)
                        p->curr = LEFT_3;
                else
                        p->curr = LEFT_1;
                move_left(&game->pos, p);
        }
        else if (p->off_y > 0)
        {
                if (p->curr == BOTTOM_1)
                        p->curr = BOTTOM_2;
                else if (p->curr == BOTTOM_2)
                        p->curr = BOTTOM_3;
                else
                        p->curr = BOTTOM_1;
                move_bottom(&game->pos, p);
        }
        else if (p->off_y < 0)
        {
                if (p->curr == TOP_1)
                        p->curr = TOP_2;
                else if (p->curr == TOP_2)
                        p->curr = TOP_3;
                else
                        p->curr = TOP_1;
                move_top(&game->pos, p);
        }
}

int _update(t_game *game)
{
        t_moving_asset *p = &game->assets->player;

        handle_moves(game, p);
        draw_offset_asset(game, p, game->pos.x, game->pos.y);
        usleep(50000);
        printf("MANY: %d\n", many++);
        return (0);
}

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
        draw_img(game, game->assets->background, 0, 0);
        /*draw(game);*/
        /*mlx_key_hook(game->window, f, game);*/
        mlx_loop_hook(game->mlx, _update, game);
        mlx_hook(game->window, 02, 1L<<0, press, game);
        /*mlx_hook(game->window, 03, 1L<<1, release, game);*/
        /*walk_left(game, &game->assets->player);*/
        mlx_loop(game->mlx);
        return (0);
}
