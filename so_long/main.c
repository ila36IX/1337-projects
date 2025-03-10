/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:49:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/09 20:59:58 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_img(t_game *game, t_data *asset, int pex_x, int pex_y)
{
        int x;
        int y;

        x = pex_x * IMG_SIZE;
        y = pex_y * IMG_SIZE;
        mlx_put_image_to_window(game->mlx, game->window, asset, x, y);
}

void move_dir(t_game *game, int x_offset, int y_offset)
{
        t_pos *c;

        c = game->assets->player->pos;
        if (c->x + x_offset >= game->map_w || c->x + x_offset < 0)
                return ;
        if (c->y + y_offset >= game->map_h || c->y + y_offset < 0)
                return ;
        if (game->map[c->y + y_offset][c->x + x_offset] == '1')
                return ;
        if (game->map[c->y + y_offset][c->x + x_offset] == 'C')
                game->collects_count--;
        if (game->map[c->y + y_offset][c->x + x_offset] == 'E' && !game->collects_count)
                quit(game, 0, "You win!");
        game->steps++;
        ft_printf("number of movements: %d\n", game->steps);
        game->map[c->y][c->x] = '0';
        game->map[c->y + y_offset][c->x + x_offset] = 'P';
        (game->assets->player->pos->x) += x_offset;
        (game->assets->player->pos->y) += y_offset;
}

void draw(t_game *game)
{
        t_assets *assets;
                int x;
        int y;

        assets = game->assets;
        y = 0;
        while (y < game->map_h)
        {
                x = 0;
                while (x < game->map_w)
                {
                        if (game->map[y][x] == '1')
                                draw_img(game, assets->wall, x, y);
                        else if (game->map[y][x] == 'C')
                                draw_img(game, assets->peel, x, y);
                        else if (game->map[y][x] == '0')
                                draw_img(game, assets->empty, x, y);
                        else if (game->map[y][x] == 'E')
                                draw_img(game, assets->exit_close, x, y);
                        else if (game->map[y][x] == 'P')
                                draw_img(game, assets->player->view, x, y);
                        x++;
                }
                y++;
        }
        if (game->map[game->exit_pos.y][game->exit_pos.x] != 'P')
                game->map[game->exit_pos.y][game->exit_pos.x] = 'E';
        draw_img(game, assets->exit_close, game->exit_pos.x, game->exit_pos.y);
        draw_img(game, assets->player->view, assets->player->pos->x, assets->player->pos->y);
}

void update_pos(t_game *game, char *direction)
{
	if (ft_strncmp(direction, "up", 2) == 0)
		move_dir(game, 0, -1);
	else if (ft_strncmp(direction, "down", 4) == 0)
		move_dir(game, 0, 1);
	else if (ft_strncmp(direction, "left", 4) == 0)
		move_dir(game, -1, 0);
	else if (ft_strncmp(direction, "right", 5) == 0)
		move_dir(game, 1, 0);
}

int     press_handler(int key_code, t_game *game)
{
        if (key_code == 100)
                update_pos(game, "right");
        if (key_code == 97)
                update_pos(game, "left");
        if (key_code == 119)
                update_pos(game, "up");
        if (key_code == 115)
                update_pos(game, "down");
        if (key_code == 65307)
                quit(game, 0, "Exiting...");
        mlx_clear_window(game->mlx, game->window);
        draw(game);
        return (0);
}


int	destroy(t_game *game)
{
	clear_game(game);
	exit(EXIT_SUCCESS);
}

void	start_game(char **map)
{
	t_game	*game;

	game = init_game((char **)map);
	game->assets = init_assets(game);
        draw(game);
	mlx_key_hook(game->window, press_handler, game);
	mlx_hook(game->window, 17, 0, destroy, game);
	mlx_loop(game->mlx);
}

/**
 * map_limit_exit - Exit if window size is bigger than the screen
 *
 * @map: map of charachters readded from file
 * Return: nothing, function will exit if window limit detected
 */
void	map_limit_exit(char **map)
{
	int	width;
	int	height;

	width = ft_strlen(map[0]);
	height = 0;
	while (map[height])
		height++;
	if (width * IMG_SIZE > MAX_WINDOW_WIDTH || height
		* IMG_SIZE > MAX_WINDOW_HEIGHT - IMG_SIZE * 2)
	{
		ft_printf("Map is solvable, but...\n");
		map_error_exit(map, "Window size is bigger than the limit");
	}
}

int	main(int ac, char *av[])
{
	char	**map;

	if (ac != 2)
	{
		ft_printf("Usage: %s path/to/map.ber\n", av[0]);
		return (0);
	}
	map = read_map(av[1]);
	map_limit_exit(map);
	start_game(map);
	return (0);
}
