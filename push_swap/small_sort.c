/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:11:56 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/28 17:23:02 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * sort_three - sort stack of size 3
 *
 * @s: pointer to stack
 * Return: Nothing, it will chnage s items order
 */
void	sort_three(t_stack *s)
{
	int	n1;
	int	n2;
	int	n3;

	if (s->size != 3)
		return ;
	n1 = get_value(s->head);
	n2 = get_value(s->head->next);
	n3 = get_value(s->tail);
	if (n1 > n2 && n1 > n3)
		rotate_a(s);
	if (n2 > n1 && n2 > n3)
		rev_rotate_a(s);
	if (get_value(s->head) > get_value(s->head->next))
		swap_a(s);
}

/**
 * min_pos - get the index of the smallest item in a stack
 *
 * @s: pointer to a stack
 * Return: Index of the smallest item in stack "s"
 */
int	min_pos(t_stack *s)
{
	t_list	*tmp;
	int		min;
	int		pos;
	int		i;

	tmp = s->head;
	min = get_value(s->head);
	pos = 0;
	i = 0;
	while (tmp)
	{
		if (get_value(tmp) < min)
		{
			min = get_value(tmp);
			pos = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (pos);
}

/**
 * sm_sort - small sort algo to sort stack with small number
 * of items efficiently
 *
 * @a: stack a
 * @b: stack b
 * Return: Nothing, it will change the order of items in stack "a"
 */
void	sm_sort(t_stack *a, t_stack *b)
{
	int	pos;

	if (a->size == 2)
	{
		if (get_value(a->head) > get_value(a->head->next))
			swap_a(a);
	}
	while (a->size > 3)
	{
		pos = min_pos(a);
		if (pos <= a->size / 2)
			while (pos-- > 0)
				rotate_a(a);
		else
			while (pos++ < a->size)
				rev_rotate_a(a);
		push_b(a, b);
	}
	sort_three(a);
	while (b->size > 0)
		push_a(a, b);
}
