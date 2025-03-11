/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_movements_0.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:53:33 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/03 02:53:43 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	walk(t_game *game, t_walker *obj, int x, int y)
{
	if (obj->off_x || obj->off_y)
		return ;
	if (!can_move(game, obj, x, y))
		return ;
	obj->off_x = x;
	obj->off_y = y;
	obj->_off_x = 0;
	obj->_off_y = 0;
}

void	move_to_next_cell(t_walker *p)
{
	if (p->off_x > 0)
		move_right(p);
	else if (p->off_x < 0)
		move_left(p);
	else if (p->off_y > 0)
		move_bottom(p);
	else if (p->off_y < 0)
		move_top(p);
}
