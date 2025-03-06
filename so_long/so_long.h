/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:12:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/04 00:58:54 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include "../libft/libft.h"
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BASE 10000
#define IMG_SIZE 64

#define FRAME_RATE 4
#define SPEED 1200
#define FRAMES 13

#define BASE_SPEED (BASE / SPEED)
#define IMAGES (((BASE / SPEED) * IMG_SIZE) / FRAMES)


#define HEADER_SIZE 120
typedef struct s_data {
        void *img;
        char *addr;
        int bits_per_pixel;
        int line_length;
        int endian;
} t_data;

enum {
        KEY_LEFT,  // 0
        KEY_RIGHT, // 1
        KEY_UP,    // 2
        KEY_DOWN,  // 3
        KEY_SPACE, // 4
};

enum {
        DIRECTION_LEFT,  // 0
        DIRECTION_RIGHT, // 1
        DIRECTION_UP,    // 2
        DIRECTION_DOWN,  // 3
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

        /* save the position before moving to erease it from screen this will
         * fix the problem of redrawing the charchter at moving
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
        t_data *exit_close;
        t_data *exit_open;

        /* dynamic */
        t_walker *player;
        t_walker **enemies;
} t_assets;

typedef struct s_game {
        void *mlx;
        void *window;
        char **map;
        char collects_count;
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

t_game *init_game(char **map);
void *init_img(t_game *game, char *path);
t_walker    **init_enemies(t_game *game);
t_assets *init_assets(t_game *game);
t_walker *init_player(t_game *game);


void draw_img(t_game *game, t_data *asset, int pex_x, int pex_y);
void walk_left(t_game *game, t_walker *asset);
void draw_walker(t_game *game, t_walker *asset);

void move_left(t_walker *asset);
void move_right(t_walker *asset);
void move_bottom(t_walker *asset);
void move_top(t_walker *asset);
void rander_steps_counter(t_game *game, int steps);
void clear_game(t_game *game);
void move_to_next_cell(t_walker *p);
int can_move(t_game *game, t_walker *obj, int x, int y);
int check_collision(t_game *game, t_walker *player, t_walker *enemy);
void walk(t_game *game, t_walker *obj, int x, int y);
int press(int keycode, t_game *game);
int release(int keycode, t_game *game);
void draw_static_objects(t_game *game);
void process_keys_events(t_game *game);
void set_next_frame_content(t_game *game);
void render(t_game *game, unsigned int curr_frame);
void move_enemies(t_game *game);
void quit(t_game *game, int key_code, char *message);
void rander_steps_counter(t_game *game, int steps);


void	free_map(char **map);

void map_checker(char **map);
void sys_error_exit(char *prefix);
void	map_error_exit(char **map, char *error);
char	**read_map(char *path);
