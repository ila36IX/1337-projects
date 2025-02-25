/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:12:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/24 14:24:17 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IMG_SIZE 64
#define FRAME_RATE IMG_SIZE / 8

typedef struct s_data {
        void *img;
        char *addr;
        int bits_per_pixel;
        int line_length;
        int endian;
} t_data;

#define FRONT 19
#define NONE 0
#define RIGHT_1 1
#define RIGHT_2 2
#define RIGHT_3 3
#define LEFT_1 4
#define LEFT_2 5
#define LEFT_3 6
#define TOP_1 7
#define TOP_2 8
#define TOP_3 9
#define BOTTOM_1 10
#define BOTTOM_2 11
#define BOTTOM_3 12

typedef struct s_moving_asset {
        t_data **views;
        int curr;
        int off_x;
        int off_y;

        /* save the position before moving to erease it from screen
         * this will fix the problem of redrawing the charchter at moving
         */
        int _off_x;
        int _off_y;
} t_moving_asset;

typedef struct s_assets {
        t_data *background;
        t_data *wall;
        t_data *empty;
        t_data *peel;
        t_moving_asset player;
        t_data *banana;
        t_data *exit;
} t_assets;

typedef struct s_pos {
        int x;
        int y;
} t_pos;

typedef struct s_game {
        void *mlx;
        void *window;
        char **map;
        int win_h; /* --- */
        int win_w; /* | */
        int map_h; /* --- */
        int map_w; /* | */
        t_assets *assets;
        t_pos pos;
        char *curr_face;
        int x_transform;
        int y_transform;
        int keycode;
} t_game;



typedef struct s_keycodes {
        int up;
        int down;
        int left;
        int right;
} t_keycodes;

t_game  *init_game(char **map);
t_assets        *init_assets(t_game *game);
void    update_pos(t_game *game, char *direction);


void draw_img(t_game *game, t_data *asset, int pex_x, int pex_y);
void walk_left(t_game *game, t_moving_asset *asset);
void draw_offset_asset(t_game *game, t_moving_asset *asset, int pex_x, int pex_y);
void transform(t_pos *, t_moving_asset *asset);
void transform_x(t_pos *, t_moving_asset *asset);
void move_left(t_pos *pos, t_moving_asset *asset);
void move_right(t_pos *pos, t_moving_asset *asset);
void move_bottom(t_pos *pos, t_moving_asset *asset);
void move_top(t_pos *pos, t_moving_asset *asset);
