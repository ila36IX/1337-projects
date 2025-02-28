/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:49:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/01 12:13:11 by aljbari          ###   ########.fr       */
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
        mlx_put_image_to_window(game->mlx, game->window, asset, x, y + 120);
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
                {
                        if (game->map[y][x] == '1')
                                draw_img(game, assets->wall, x, y);
                        else if (game->map[y][x] == 'C')
                                draw_img(game, assets->peel, x, y);
                        else if (game->map[y][x] == 'P')
                                draw_img(game, assets->player->views[STAND_1], x, y);
                }
        }
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


int can_move(t_game *game, t_walker *obj, int x, int y)
{
        int next_y;// next_y = obj->pos->x + (x > 0 ? 1 : (x == 0 ? 0 : -1));
        int next_x; //next_x = obj->pos->y + (y > 0 ? 1 : (y == 0 ? 0 : -1));
        char c;

        next_y = obj->pos->y + -1 * (y < 0) + (y > 0);
        next_x = obj->pos->x + -1 * (x < 0) + (x > 0);
        if (next_y < 0 || next_y > game->map_h - 1 || next_x < 0 || next_x > game->map_w - 1)
                return (0);
        c = game->map[next_y][next_x];
        if (c == '1')
                return (0);
        if (c == 'C')
        {
                if (game->assets->player == obj)
                {
                        game->map[next_y][next_x] = '0';
                        printf("COLLECTABLE HAVE BEEN TAKEN\n");
                }
                else
                        return (0);
        }
        if (obj == game->assets->player)
                game->steps++;
        return (1);
}

void walk(t_game *game, t_walker *obj, int x, int y)
{
        if (obj->off_x || obj->off_y)
                return ;
        if (!can_move(game, obj, x, y))
                return ;
        obj->off_x = x;
        obj->off_y = y;
        obj->_off_x = 0;
        obj->_off_y = 0;
}

/* Todo: Double free accures because this function is called many times */
void quit(t_game *game)
{
        /*mlx_loop_end (game->mlx);*/
        /*mlx_destroy_window(game->mlx, game->window);*/
        clear_game(game);

        /* Free everything... */
        exit(0);
}
void    reset_kyes(t_game *game)
{
        game->keycode[KEY_RIGHT] = 0;
        game->keycode[KEY_LEFT] = 0;
        game->keycode[KEY_UP] = 0;
        game->keycode[KEY_DOWN] = 0;
}

unsigned int many;

int	press(int keycode, t_game *game)
{
        t_walker *w;

        w = game->assets->player;
        if (keycode == 65307)
                quit(game);
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


void update_face(int *index, int start)
{
        if (*index <= start + 1 && *index >= start)
                ++*index;
        else
                *index = start;
}

void next_img(t_game *game, t_walker *p)
{
        if (!p->off_x && !p->off_y)
        {
                for (int i = 0; i < 4; i++)
                        if (game->keycode[i])
                                return ;
                update_face(&p->curr, STAND_1);
        }
        else if (p->off_x > 0)
                update_face(&p->curr, RIGHT_1);
        else if (p->off_x < 0)
                update_face(&p->curr, LEFT_1);
        else if (p->off_y > 0)
                update_face(&p->curr, BOTTOM_1);
        else if (p->off_y < 0)
                update_face(&p->curr, TOP_1);

}


void process_keys_events(t_game *game)
{
        t_walker *w = game->assets->player;

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
        printf("\n");
        printf("%10s: %10d\n", "STEPS", game->steps);
        printf("%10s: (%d, %d)\n", "ENEMY 0", game->assets->enemies[0]->pos->x,
               game->assets->enemies[0]->pos->y);
        printf("%10s: (%d, %d)\n", "GRID", game->assets->enemies[0]->pos->x,
               game->assets->player->pos->y);
        printf("%10s: (%d, %d)\n", "OFFSET", game->assets->enemies[0]->off_x,
               game->assets->enemies[0]->off_y);
        printf("%10s: (%d, %d)\n", "_OFFSET", game->assets->enemies[0]->_off_x,
               game->assets->player->_off_y);
        printf("%10s: %d\n", "DIRECTION", game->assets->enemies[0]->direction);
        printf("%10s: %10d\n", "LOOPS", i);

        /* Sepirator */
        printf("\n");
}

#include <time.h>

void move_enemies(t_game *game, unsigned int curr_frame)
{
        int i = 0;
        t_walker **enemies;
        int random_number;

        enemies = game->assets->enemies;
        srand(time(NULL));
        while (enemies[i])
        {
                random_number = rand() % 4;
                enemies[i]->direction = random_number;
                if (enemies[i]->direction == DIRECTION_DOWN && can_move(game, enemies[i], 0, FRAME_RATE))
                        walk(game, enemies[i], 0, FRAME_RATE);
                else if (enemies[i]->direction == DIRECTION_UP && can_move(game, enemies[i], 0, -FRAME_RATE))
                        walk(game, enemies[i], 0, -FRAME_RATE);
                else if (enemies[i]->direction == DIRECTION_RIGHT && can_move(game, enemies[i], FRAME_RATE, 0))
                        walk(game, enemies[i], FRAME_RATE, 0);
                else if (enemies[i]->direction == DIRECTION_LEFT && can_move(game, enemies[i], -FRAME_RATE, 0))
                        walk(game, enemies[i], -FRAME_RATE, 0);
                else
                {
                        enemies[i]->direction++;
                        if (enemies[i]->direction > DIRECTION_DOWN)
                                enemies[i]->direction = curr_frame % 4;
                }
                move_to_next_cell(game, enemies[i]);
                draw_walker(game, enemies[i]);
                i++;
        }

}
int abs(int n)
{
        if (n < 0)
                return (n * -1);
        else
                return (n);

}
int collision(t_walker *player, t_walker *enemy)
{
        int enemy_x;
        int player_x;
        int enemy_y;
        int player_y;
        static unsigned int collisions_cout;

        enemy_x = enemy->off_x + enemy->pos->x * IMG_SIZE;
        enemy_y = enemy->off_y + enemy->pos->y * IMG_SIZE;
        player_x = player->off_x + player->pos->x * IMG_SIZE;
        player_y = player->off_y + player->pos->y * IMG_SIZE;
        if (abs(enemy_x - player_x) < IMG_SIZE && abs(enemy_y - player_y) < IMG_SIZE)
        {
                printf("You've been elimenated by the monster :(\n");
                exit(1);
                collisions_cout++;

        }
        return (1);
}

void rander(t_game *game, unsigned int i)
{
        t_walker *player = game->assets->player;
        static unsigned int many_prints;

        if (i % BASE_SPEED == 0)
        {
                int i = 0;
                while (game->assets->enemies[i])
                {
                        collision(game->assets->player, game->assets->enemies[i]);
                        i++;
                }
                move_enemies(game, i);
                move_to_next_cell(game, player);
                draw_walker(game, player);
                rander_steps_counter(game, game->steps);
        }
        if (i % IMAGES == 0)
        {
                next_img(game, player);
                next_img(game, game->assets->enemies[0]);
                next_img(game, game->assets->enemies[1]);
                next_img(game, game->assets->enemies[2]);
        }
}

int _update(t_game *game)
{
        static unsigned int curr_frame;

        curr_frame++;
        process_keys_events(game);
        rander(game, curr_frame);
        usleep(2000);
        /*debug(game, curr_frame);*/
        return (0);
}

int	main(void)
{
        t_game *game;
        t_assets *assets;
        char *map[100] = {
                strdup("11111111111111111111111111"),
                strdup("1P000000000000000000C00001"),
                strdup("1000000E000000000000C00001"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010000000000001"),
                strdup("11111011111111111110111111"),
                strdup("10000000000010000000000001"),
                strdup("10000000000010E00000C00001"),
                strdup("100000E0000010000000000001"),
                strdup("10000000000000000000C00001"),
                strdup("100000000000100E0000000001"),
                strdup("10000000000010000000E00001"),
                strdup("11111111111111111111111111"),
                NULL
        };

        game = init_game((char **) map);
        assets = init_assets(game);
        game->assets = assets;
        draw_img(game, game->assets->background, 0, 0);
        draw_walker(game, game->assets->player);
        draw(game);
        /*mlx_key_hook(game->window, press, game);*/
        mlx_loop_hook(game->mlx, _update, game);
        mlx_hook(game->window, 2, 1L<<0, press, game);
        mlx_do_key_autorepeaton(game->mlx);
        mlx_hook(game->window, 3, 1L<<1, release, game);
        /*walk_left(game, &game->assets->player);*/
        mlx_loop(game->mlx);
        return (0);
}
