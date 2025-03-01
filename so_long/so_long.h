/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:12:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/28 19:18:04 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BASE 10000 
#define IMG_SIZE 64

#define FRAME_RATE 4
#define SPEED 1200
#define FRAMES 13

#define BASE_SPEED (BASE / SPEED)
#define IMAGES (((BASE / SPEED) * IMG_SIZE) / FRAMES)

typedef struct s_data {
        void *img;
        char *addr;
        int bits_per_pixel;
        int line_length;
        int endian;
} t_data;

typedef enum {
        KEY_LEFT,    // 0
        KEY_RIGHT,   // 1
        KEY_UP,      // 2
        KEY_DOWN,    // 3
        KEY_SPACE,   // 4
} KeyCode;

enum {
        DIRECTION_LEFT,    // 0
        DIRECTION_RIGHT,   // 1
        DIRECTION_UP,      // 2
        DIRECTION_DOWN,    // 3
};


enum {
        RIGHT_1,
        RIGHT_2,
        RIGHT_3,
        LEFT_1,
        LEFT_2,
        LEFT_3,
        TOP_1,
        TOP_2,
        TOP_3,
        BOTTOM_1,
        BOTTOM_2,
        BOTTOM_3,
        STAND_1,
        STAND_2,
        STAND_3,
        VIEWS_END,
};

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
        int direction;
        t_pos *pos;
} t_walker;

typedef struct s_assets {
        /* static */
        t_data *background;
        t_data *header;
        t_data *header_counter;
        t_data *wall;
        t_data *empty;
        t_data *peel;
        t_data **numbers;
        t_data *exit;

        /* dynamic */
        t_walker *player;
        t_walker **enemies;
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
        int *keycode;
        int speed;
        int frames;
        unsigned int steps;
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
void    rander_steps_counter(t_game *game, int steps);
void clear_game(t_game *game);
void    move_to_next_cell(t_game *game, t_walker *p);
