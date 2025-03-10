/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:12:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/09 21:03:07 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../libft/libft.h"
# include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>

# define IMG_SIZE 64
# define MAX_WINDOW_WIDTH 3840
# define MAX_WINDOW_HEIGHT 2160

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;



typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;

/* current view index */
/* all available frames of the walker */
/* save the position before moving to erease it from screen this will
 * fix the problem of redrawing the charchter at moving
 */
typedef struct s_walker
{
	t_data			*view;
	int				direction;
	t_pos			*pos;
}					t_walker;

typedef struct s_assets
{
	t_data			*background;
	t_data			*wall;
	t_data			*empty;
	t_data			*peel;
	t_data			*exit_close;
	t_data			*exit_open;
	t_walker		*player;
}					t_assets;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	char			**map;
	char			collects_count;
	int				win_h;
	int				win_w;
	int				map_h;
	int				map_w;
	t_assets		*assets;
	unsigned int	steps;
	t_pos			exit_pos;
}					t_game;

/* init game */
t_game				*init_game(char **map);
void				*init_img(t_game *game, char *path);
t_assets			*init_assets(t_game *game);
t_walker			*init_player(t_game *game);

/* randers */
void				draw_img(t_game *game, t_data *asset, int pex_x, int pex_y);

/* Memory release */
void				quit(t_game *game, int exit_code, char *message);
void				clear_game(t_game *game);
void				free_map(char **map);
void				free_ids(int **ids, int height);

/* error handlers */
void				sys_error_exit(char *prefix);
void				map_error_exit(char **map, char *error);
void exit_if_not_solvable(char **map, int **ids, int width, int height);

/* file to matrix */
char				**read_map(char *path);

/* Parsing */
void				map_checker(char **map);
void				check_map_solveability(char **map);

#endif
