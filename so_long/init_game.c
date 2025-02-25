/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:28:11 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/25 13:54:33 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
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
        game->win_h = game->map_h * IMG_SIZE;
        game->win_w = game->map_w * IMG_SIZE;
        game->window = mlx_new_window(game->mlx, game->win_w, game->win_h, "Banana");
        /*t_pos pos;*/
        /*for (int y = 0; y < game->map_h; y++) {*/
        /*        for (int x = 0; x < game->map_w; x++)*/
        /*                if (map[y][x] == 'P') {*/
        /*                        pos.x = x;*/
        /*                        pos.y = y;*/
        /*                }*/
        /*}*/
        // game->pos = pos;
        t_pos test = {0, 0};
        return (game);
}

t_assets *init_assets(t_game *game)
{
        t_assets *assets;
        t_walker *player = malloc(sizeof(t_walker)); 
        t_data **views;

        assets = malloc(sizeof(t_assets));
        assets->wall = init_img(game, "./images/wall.xpm");
        assets->peel = init_img(game, "./images/peel.xpm");
        assets->empty = init_img(game, "./images/empty.xpm");
        assets->banana = init_img(game, "./images/banana_front.xpm");
        assets->background = init_img(game, "./images/background.xpm");
        views = malloc(sizeof(t_data) * 40);
        views[NONE] = init_img(game, "./images/empty.xpm");        
        views[FRONT] = init_img(game, "./images/banana_left1.xpm");        
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
        player->views = views;
        player->off_x = 0;
        player->off_y = 0;
        player->_off_x = 0;
        player->_off_y = 0;
        player->curr = 1;
        assets->player = player;
        assets->player->pos = malloc(sizeof(t_pos));
        assets->player->pos->x = 0;
        assets->player->pos->y = 0;
        return (assets);
}

void put_pixel(t_data *data, int x, int y, int color)
{
        char *dst;

        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
}
