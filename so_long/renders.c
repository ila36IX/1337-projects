#include "so_long.h"

void render(t_game *game, unsigned int curr_frame)
{
        t_walker *player;
        int     j;

        j = 0;
        player = game->assets->player;
        if (curr_frame % BASE_SPEED == 0)
        {
                while (game->assets->enemies[j])
                        collision(game->assets->player, game->assets->enemies[j++]);
                move_enemies(game, curr_frame);
                move_to_next_cell(game, player);
                draw_walker(game, player);
                rander_steps_counter(game, game->steps);
        }
        if (curr_frame % IMAGES == 0)
                set_next_frame_content(game);
}

void draw_walker(t_game *game, t_walker *charachter)
{
        int x;
        int y;
        t_data *view;
        t_data *erase;

        view = charachter->views[charachter->curr];
        erase = game->assets->empty;
        mlx_put_image_to_window(game->mlx, game->window, erase,
                                charachter->pos->x * IMG_SIZE + charachter->_off_x,
                                charachter->pos->y * IMG_SIZE + charachter->_off_y + 120);
        mlx_put_image_to_window(game->mlx, game->window, view,
                                charachter->pos->x * IMG_SIZE + charachter->off_x,
                                charachter->pos->y * IMG_SIZE + charachter->off_y + 120);
        charachter->_off_x = charachter->off_x;
        charachter->_off_y = charachter->off_y;
}

void draw_img(t_game *game, t_data *asset, int pex_x, int pex_y)
{
        int x;
        int y;

        x = pex_x * IMG_SIZE;
        y = pex_y * IMG_SIZE;
        mlx_put_image_to_window(game->mlx, game->window, asset, x, y + 120);
}

void draw(t_game *game)
{
        t_assets *assets;

        assets = game->assets;
        draw_img(game, game->assets->background, 0, 0);
        for (int y = 0; y < game->map_h; y++)
        {
                for (int x = 0; x < game->map_w; x++)
                {
                        if (game->map[y][x] == '1')
                                draw_img(game, assets->wall, x, y);
                        else if (game->map[y][x] == 'C')
                                draw_img(game, assets->peel, x, y);
                        else if (game->map[y][x] == 'P')
                                draw_img(game, assets->player->views[STAND_1], x, y);
                        else if (game->map[y][x] == 'E')
                                draw_img(game, assets->exit_close, x, y);
                }
        }
}
