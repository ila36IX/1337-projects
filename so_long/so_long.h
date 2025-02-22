/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:12:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/02/08 13:00:14 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define IMG_SIZE 40

typedef struct	s_data {
  void	*img;
  char	*addr;
  int		bits_per_pixel;
  int		line_length;
  int		endian;
}				t_data;

typedef struct s_fr {
  void *mlx;
  void *window;
  t_data *frame;
} t_fr;

typedef struct s_assets {
  t_data *wall;
  t_data *empty;
  t_data *peel;
  t_data *banana;
  t_data *banana_left;
  t_data *banana_right;
  t_data *banana_up;
  t_data *banana_down;
  t_data *exit;
} t_assets;

typedef struct s_pos
{
  int	x;
  int	y;
} t_pos;

typedef struct s_game
{
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
} t_game;

typedef struct s_keycodes {
  int up;
  int down;
  int left;
  int right;
} t_keycodes;

t_game  *init_game(char **map);
t_assets *init_assets(t_game *game);
void update_pos(t_game *game, char *direction);
