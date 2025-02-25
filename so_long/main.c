/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:49:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/25 13:53:55 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


void draw_img(t_game *game, t_data *asset, int pex_x, int pex_y)
{
        int x;
        int y;

        x = pex_x * IMG_SIZE;
        y = pex_y * IMG_SIZE;
        mlx_put_image_to_window(game->mlx, game->window, asset, x, y);
}

/*void walk(t_game *game, void *object)*/
/*{*/
/*        t_assets *assets;*/
/**/
/*        assets = game->assets;*/
/*        for (int y = 0; y < game->map_h; y++)*/
/*        {*/
/*                for (int x = 0; x < game->map_w; x++)*/
/*                        if (game->map[y][x] == '1')*/
/*                                draw_img(game, assets->wall, x, y);*/
/*                        else if (game->map[y][x] == 'C')*/
/*                                draw_img(game, assets->peel, x, y);*/
/*                        else if (game->map[y][x] == 'P')*/
/*                                draw_img(game, assets->banana, x, y);*/
/*        }*/
/*}*/

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
int	release(int keycode, t_game *game)
{
        if (keycode == game->keycode)
                game->keycode = 0;
        return (0);
}

int can_move(t_game *game, t_walker *obj, int x, int y)
{
        int next_y;// next_y = obj->pos->x + (x > 0 ? 1 : (x == 0 ? 0 : -1));
        int next_x; //next_x = obj->pos->y + (y > 0 ? 1 : (y == 0 ? 0 : -1));
        char c;

        next_y = obj->pos->y + -1 * (y < 0) + (y > 0);
        next_x = obj->pos->x + -1 * (x < 0) + (x > 0);
        /*if (y > 0)*/
        /*        next_y = obj->pos->x + 1;*/
        /*else if (x == 0)*/
        /*        next_y = obj->pos->x;*/
        /*else*/
        /*        next_y = obj->pos->x - 1;*/
        /*if (x > 0)*/
        /*        next_x = obj->pos->y + 1;*/
        /*else if (y == 0)*/
        /*        next_x = obj->pos->y;*/
        /*else*/
        /*        next_x = obj->pos->y - 1;*/
        if (next_y < 0 || next_y > game->map_h - 1 || next_x < 0 || next_x > game->map_w - 1)
                return (0);
        c = game->map[next_y][next_x];
        if (c == '1')
                return (0);
        return (1);
}

void walk(t_game *game, t_walker *obj, int x, int y)
{
        if (!can_move(game, obj, x, y))
        {
                game->keycode = 0;
                return ;
        }
        obj->off_x = x;
        obj->off_y = y;
        obj->_off_x = 0;
        obj->_off_y = 0;
}

/* Todo: Double free accures because this function is called many times */
void quit(t_game *game)
{
        mlx_loop_end (game->mlx);
        mlx_destroy_window(game->mlx, game->window);

        /* Free everything... */
}
int	press(int keycode, t_game *game)
{
        t_walker *w;

        w = game->assets->player;
        if (keycode == 65307)
                quit(game);
        game->keycode = keycode;
        if (w->off_x || w->off_y)
                return (0);
        keycode = game->keycode;
        if (keycode == 100)
                walk(game, w, FRAME_RATE, 0);
        if (keycode == 97)
                walk(game, w, -FRAME_RATE, 0);
        if (keycode == 119)
                walk(game, w, 0, -FRAME_RATE);
        if (keycode == 115)
                walk(game, w, 0, FRAME_RATE);
        printf("KEY: %d\n", keycode);
        return (0);
}

int many;

void update_face(int *index, int start)
{
        if (*index <= start + 1 && *index >= start)
                ++*index;
        else
                *index = start;
}

void    handle_moves(t_game *game, t_walker *p)
{
        if (p->off_x > 0)
        {
                update_face(&p->curr, RIGHT_1);
                move_right(p);
        }
        else if (p->off_x < 0)
        {
                update_face(&p->curr, LEFT_1);
                move_left(p);
        }
        else if (p->off_y > 0)
        {
                update_face(&p->curr, BOTTOM_1);
                move_bottom(p);
        }
        else if (p->off_y < 0)
        {
                update_face(&p->curr, TOP_1);
                move_top(p);
        }
}

int _update(t_game *game)
{
        t_walker *p = game->assets->player;

        handle_moves(game, p);
        if (p->off_x || p->off_y)
                draw_walker(game, p);
        if (game->keycode)
                press(game->keycode, game);
        usleep(55000);
        /*printf("MANY: %d\n", many++);*/
        return (0);
}

int	main(void)
{
        t_game *game;
        t_assets *assets;
        char *map[100] = {
                strdup("10000000000000000000C00001"),
                strdup("10000000000000000000C00001"),
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
        draw_walker(game, game->assets->player);
        draw(game);
        /*mlx_key_hook(game->window, f, game);*/
        mlx_loop_hook(game->mlx, _update, game);
        mlx_hook(game->window, 02, 1L<<0, press, game);
        mlx_hook(game->window, 03, 1L<<1, release, game);
        /*walk_left(game, &game->assets->player);*/
        mlx_loop(game->mlx);
        return (0);
}
