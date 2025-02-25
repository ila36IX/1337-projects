/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:12:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/25 13:59:41 by aljbari          ###   ########.fr       */
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
#define STAND_1 13
#define STAND_2 14
#define STAND_3 15

typedef struct s_pos {
        int x;
        int y;
} t_pos;

typedef struct s_walker {
        /* all available frames of the walker */
        t_data **views;
        /* current view index */
        int curr;
        int off_x;
        int off_y;

        /* save the position before moving to erease it from screen
         * this will fix the problem of redrawing the charchter at moving
         */
        int _off_x;
        int _off_y;
        t_pos *pos;
} t_walker;

typedef struct s_assets {
        /* static */
        t_data *background;
        t_data *wall;
        t_data *empty;
        t_data *peel;
        t_data *banana;
        t_data *exit;

        /* dynamic */
        t_walker *player;
} t_assets;


typedef struct s_game {
        void *mlx;
        void *window;
        char **map;
        int win_h; /* --- */
        int win_w; /* | */
        int map_h; /* --- */
        int map_w; /* | */
        t_assets *assets;
        char *curr_face;
        int x_transform;
        int y_transform;
        int keycode;
} t_game;


t_game  *init_game(char **map);
t_assets        *init_assets(t_game *game);
void    update_pos(t_game *game, char *direction);


void    draw_img(t_game *game, t_data *asset, int pex_x, int pex_y);
void    walk_left(t_game *game, t_walker *asset);
void    draw_walker(t_game *game, t_walker *asset);

void	move_left(t_walker *asset);
void	move_right(t_walker *asset);
void	move_bottom(t_walker *asset);
void	move_top(t_walker *asset);
