/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:18:12 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/02 18:04:25 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <time.h>

void move_enemies(t_game *game, unsigned int curr_frame)
{
        int i = 0;
        t_walker **enemies;

        enemies = game->assets->enemies;
        srand(time(NULL));
        while (enemies[i])
        {
                enemies[i]->direction = rand() % 4;;
                if (enemies[i]->direction == DIRECTION_DOWN && can_move(game, enemies[i], 0, FRAME_RATE))
                        walk(game, enemies[i], 0, FRAME_RATE);
                else if (enemies[i]->direction == DIRECTION_UP && can_move(game, enemies[i], 0, -FRAME_RATE))
                        walk(game, enemies[i], 0, -FRAME_RATE);
                else if (enemies[i]->direction == DIRECTION_RIGHT && can_move(game, enemies[i], FRAME_RATE, 0))
                        walk(game, enemies[i], FRAME_RATE, 0);
                else if (enemies[i]->direction == DIRECTION_LEFT && can_move(game, enemies[i], -FRAME_RATE, 0))
                        walk(game, enemies[i], -FRAME_RATE, 0);
                move_to_next_cell(game, enemies[i]);
                draw_walker(game, enemies[i]);
                i++;
        }
}

int collision(t_walker *player, t_walker *enemy)
{
        int enemy_x;
        int player_x;
        int enemy_y;
        int player_y;

        enemy_x = enemy->off_x + enemy->pos->x * IMG_SIZE;
        enemy_y = enemy->off_y + enemy->pos->y * IMG_SIZE;
        player_x = player->off_x + player->pos->x * IMG_SIZE;
        player_y = player->off_y + player->pos->y * IMG_SIZE;
        if (abs(enemy_x - player_x) < IMG_SIZE && abs(enemy_y - player_y) < IMG_SIZE)
        {
                printf("You've been elimenated by the monster :(\n");
                exit(0);
        }
        return (1);
}

int enemy_can_move(t_game *game, t_walker *obj, int x, int y)
{
        int next_y;
        int next_x;

        next_y = obj->pos->y + -1 * (y < 0) + (y > 0);
        next_x = obj->pos->x + -1 * (x < 0) + (x > 0);
        if (next_y < 0 || next_y > game->map_h - 1 || next_x < 0 || next_x > game->map_w - 1)
                return (0);
        if (game->map[next_y][next_x] == '0' || game->map[next_y][next_x] == 'P')
                return (1);
        else
                return (0);
}

int player_can_move(t_game *game, t_walker *obj, int x, int y)
{
        int next_y;
        int next_x;

        next_y = obj->pos->y + -1 * (y < 0) + (y > 0);
        next_x = obj->pos->x + -1 * (x < 0) + (x > 0);
        if (next_y < 0 || next_y > game->map_h - 1 || next_x < 0 || next_x > game->map_w - 1)
                return (0);
        if (game->map[next_y][next_x] == '1')
                return (0);
        if (game->map[next_y][next_x] == 'E' && game->collects_count == 0)
        {
                /* Free everything */
                exit(0);
                return (1);
        }
        if (game->map[next_y][next_x] == 'E'&& game->collects_count != 0)
                return (0);
        if (game->map[next_y][next_x] == 'C')
        {
                game->map[next_y][next_x] = '0';
                game->collects_count--;
        }
        game->steps++;
        return (1);
}

int can_move(t_game *game, t_walker *obj, int x, int y)
{
        if (obj == game->assets->player)
                return (player_can_move(game, obj, x, y));
        else
                return (enemy_can_move(game, obj, x, y));
}
