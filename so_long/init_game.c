/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:28:11 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/02 18:18:17 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>
#include <stdlib.h>

void *init_img(t_game *game, char *path)
{
        int w;
        int h;
        void *img;

        img = NULL;
        img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
        if (img)
                return (img);
        else
        {
                printf("Img init Error: \"%s\" exists?", path);
                exit(200);
        }
}

t_game *init_game(char **map) {
        t_game *game;

        game = malloc(sizeof(t_game));
        game->mlx = mlx_init();
        game->map = map;
        game->map_w = strlen(map[0]);
        game->map_h = 0;
        while (map[game->map_h])
                (game->map_h)++;
        game->win_h = game->map_h * IMG_SIZE + 120;
        game->win_w = game->map_w * IMG_SIZE;
        game->window = mlx_new_window(game->mlx, game->win_w, game->win_h, "Banana");
        game->collects_count = 0;
        for (int y = 0; y < game->map_h; y++) {
                for (int x = 0; x < game->map_w; x++)
                        if (map[y][x] == 'C')
                                game->collects_count++;
        }
        return (game);
}

t_walker *init_player(t_game *game)
{

        t_walker *player;
        t_data **views;

        player = malloc(sizeof(t_walker)); 
        views = malloc(sizeof(t_data) * VIEWS_END + 1);
        views[LEFT_1] = init_img(game, "./images/banana_left1.xpm");        
        views[LEFT_2] = init_img(game, "./images/banana_left2.xpm");        
        views[LEFT_3] = init_img(game, "./images/banana_left3.xpm");        
        views[RIGHT_1] = init_img(game, "./images/banana_right1.xpm");        
        views[RIGHT_2] = init_img(game, "./images/banana_right2.xpm");        
        views[RIGHT_3] = init_img(game, "./images/banana_right3.xpm");        
        views[TOP_1] = init_img(game, "./images/banana_top1.xpm");        
        views[TOP_2] = init_img(game, "./images/banana_top2.xpm");        
        views[TOP_3] = init_img(game, "./images/banana_top3.xpm");        
        views[BOTTOM_1] = init_img(game, "./images/banana_bottom1.xpm");        
        views[BOTTOM_2] = init_img(game, "./images/banana_bottom2.xpm");        
        views[BOTTOM_3] = init_img(game, "./images/banana_bottom3.xpm");        
        views[STAND_1] = init_img(game, "./images/stand1.xpm");        
        views[STAND_2] = init_img(game, "./images/stand2.xpm");        
        views[STAND_3] = init_img(game, "./images/stand3.xpm");  
        views[VIEWS_END] = NULL;
        player->views = views;
        player->off_x = 0;
        player->off_y = 0;
        player->_off_x = 0;
        player->_off_y = 0;
        player->curr = STAND_1;
        player->pos = malloc(sizeof(t_pos));
        for (int y = 0; y < game->map_h; y++)
        {
                for (int x = 0; x < game->map_w; x++)
                        if (game->map[y][x] == 'P')
                        {
                                player->pos->x = x;
                                player->pos->y = y;
                        }
        }
        return (player);
}

void    rander_steps_counter(t_game *game, int steps)
{
        mlx_put_image_to_window(game->mlx, game->window,
                                game->assets->numbers[(steps / 1000) % 10],
                                264 - 40 * 3, 30);
        mlx_put_image_to_window(game->mlx, game->window,
                                game->assets->numbers[(steps / 100) % 10],
                                264 - 40 * 2, 30);
        mlx_put_image_to_window(game->mlx, game->window,
                                game->assets->numbers[(steps / 10) % 10], 264 - 40,
                                30);
        mlx_put_image_to_window(game->mlx, game->window,
                                game->assets->numbers[steps % 10], 264, 30);
}

t_walker        *init_enemy(t_game *game, int x, int y)
{
        t_walker *enemy;
        t_data **views;

        enemy = malloc(sizeof(t_walker)); 
        views = malloc(sizeof(t_data) * VIEWS_END + 1);
        views[LEFT_1] = init_img(game, "./images/monster_left1.xpm");        
        views[LEFT_2] = init_img(game, "./images/monster_left2.xpm");        
        views[LEFT_3] = init_img(game, "./images/monster_left3.xpm");        
        views[RIGHT_1] = init_img(game, "./images/monster_right1.xpm");        
        views[RIGHT_2] = init_img(game, "./images/monster_right2.xpm");        
        views[RIGHT_3] = init_img(game, "./images/monster_right1.xpm");        
        views[TOP_1] = init_img(game, "./images/monster_up1.xpm");        
        views[TOP_2] = init_img(game, "./images/monster_up2.xpm");        
        views[TOP_3] = init_img(game, "./images/monster_up3.xpm");        
        views[BOTTOM_1] = init_img(game, "./images/monster_down1.xpm");        
        views[BOTTOM_2] = init_img(game, "./images/monster_down2.xpm");        
        views[BOTTOM_3] = init_img(game, "./images/monster_down3.xpm");        
        views[STAND_1] = init_img(game, "./images/monster_right1.xpm");        
        views[STAND_2] = init_img(game, "./images/monster_right2.xpm");        
        views[STAND_3] = init_img(game, "./images/monster_right3.xpm");  
        views[VIEWS_END] = NULL;
        enemy->views = views;
        enemy->off_x = 0;
        enemy->off_y = 0;
        enemy->_off_x = 0;
        enemy->_off_y = 0;
        enemy->curr = STAND_1;
        enemy->pos = malloc(sizeof(t_pos));
        enemy->pos->x = x;
        enemy->pos->y = y;
        enemy->direction = DIRECTION_LEFT;
        return (enemy);
}

t_walker    **init_enemies(t_game *game)
{

        int i = 0;
        t_walker **enemies;

        enemies = malloc(sizeof(t_walker) * 10);
        for (int y = 0; y < game->map_h; y++)
        {
                for (int x = 0; x < game->map_w; x++)
                        if (game->map[y][x] == 'M')
                        {
                                enemies[i] = init_enemy(game, x, y);
                                game->map[y][x] = '0';
                                i++;
                        }
        }
        enemies[i] = NULL;
        return (enemies);
}

t_assets *init_assets(t_game *game)
{
        t_assets *assets;

        assets = malloc(sizeof(t_assets));
        assets->wall = init_img(game, "./images/wall.xpm");
        assets->peel = init_img(game, "./images/peel.xpm");
        assets->empty = init_img(game, "./images/empty.xpm");
        assets->background = init_img(game, "./images/background.xpm");
        assets->exit_close = init_img(game, "./images/trash_closed.xpm");
        assets->exit_open = init_img(game, "./images/trash_open.xpm");
        assets->numbers = malloc(sizeof(t_data) * 10);
        assets->numbers[0] = init_img(game, "./images/digit0.xpm");
        assets->numbers[1] = init_img(game, "./images/digit1.xpm");
        assets->numbers[2] = init_img(game, "./images/digit2.xpm");
        assets->numbers[3] = init_img(game, "./images/digit3.xpm");
        assets->numbers[4] = init_img(game, "./images/digit4.xpm");
        assets->numbers[5] = init_img(game, "./images/digit5.xpm");
        assets->numbers[6] = init_img(game, "./images/digit6.xpm");
        assets->numbers[8] = init_img(game, "./images/digit8.xpm");
        assets->numbers[7] = init_img(game, "./images/digit7.xpm");
        assets->numbers[9] = init_img(game, "./images/digit9.xpm");
        assets->header_counter = init_img(game, "./images/banner_with_steps_counter.xpm");
        assets->header = init_img(game, "./images/banner.xpm");
        mlx_put_image_to_window(game->mlx, game->window, assets->header_counter, 0, 0);
        int x = 600;
        while (x < game->win_w)
        {
                mlx_put_image_to_window(game->mlx, game->window, assets->header, x, 0);
                x += 600;
        }
        assets->player = init_player(game);
        assets->enemies = init_enemies(game);
        game->keycode = malloc(sizeof(int) * 4);
        game->keycode[0] = 0;
        game->keycode[1] = 0;
        game->keycode[2] = 0;
        game->keycode[3] = 0;
        game->speed = 0;
        game->frames = 0;
        game->steps = 0;
        return (assets);
}


void put_pixel(t_data *data, int x, int y, int color)
{
        char *dst;

        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
}
