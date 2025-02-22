/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:28:11 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/21 17:28:13 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void *init_img(t_game *game, char *path) {
        int w;
        int h;

        return (mlx_xpm_file_to_image(game->mlx, path, &w, &h));
}

t_game *init_game(char **map) {
        t_game *game;
        t_pos pos;

        game = malloc(sizeof(t_game));
        game->mlx = mlx_init();
        ;
        game->map = map;
        game->map_w = strlen(map[0]);
        game->map_h = 0;
        while (map[game->map_h])
                (game->map_h)++;
        game->win_h = game->map_h * IMG_SIZE;
        game->win_w = game->map_w * IMG_SIZE;
        game->window = mlx_new_window(game->mlx, game->win_w, game->win_h, "Banana");
        for (int y = 0; y < game->map_h; y++) {
                for (int x = 0; x < game->map_w; x++)
                        if (map[y][x] == 'P') {
                                pos.x = x;
                                pos.y = y;
                        }
        }
        game->pos = pos;
        return (game);
}

t_assets *init_assets(t_game *game) {
        t_assets *assets;

        assets = malloc(sizeof(t_assets));
        assets->wall = init_img(game, "./images/wall.xpm");
        assets->peel = init_img(game, "./images/peel.xpm");
        assets->empty = init_img(game, "./images/empty.xpm");
        assets->banana = init_img(game, "./images/banana_front.xpm");
        return (assets);
}

void put_pixel(t_data *data, int x, int y, int color) {
        char *dst;

        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
}

t_data *init_asset(void *mlx, int x_size, int y_size, int color) {
        t_data *fr;

        fr = malloc(sizeof(t_data));
        fr->img = mlx_new_image(mlx, x_size, y_size);
        fr->addr = mlx_get_data_addr(fr->img, &fr->bits_per_pixel, &fr->line_length,
                                     &fr->endian);
        for (int i = 0; i < x_size; i++)
                put_pixel(fr, i, 0, color);
        for (int i = 0; i < x_size; i++)
                put_pixel(fr, i, y_size - 1, color);
        for (int i = 0; i < y_size; i++)
                put_pixel(fr, 0, i, color);
        for (int i = 0; i < y_size; i++)
                put_pixel(fr, x_size - 1, i, color);
        return (fr);
}
