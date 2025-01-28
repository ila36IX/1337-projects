/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ksort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:32:07 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/28 16:15:20 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * bigger_index - find the index of the max value in stack a
 *
 * @a: Pointer to stack a
 * Return: Index where the max item is located in a
 */
int	bigger_index(t_stack *a)
{
	int		i;
	int		big;
	int		big_idx;
	t_list	*walk;

	walk = a->head;
	big = get_value(walk);
	big_idx = 0;
	i = 0;
	while (walk)
	{
		if (get_value(walk) > big)
		{
			big = get_value(walk);
			big_idx = i;
		}
		i++;
		walk = walk->next;
	}
	return (big_idx);
}

/**
 * sort_stack - call to action main algorithm
 * - It pushs all value in a into b using the slow/fast algo
 * - than it pushs back all items in b into a, by finding every
 *   time the max in b and push it using rotate or rev-rotate
 *   that depends on where the max is located (above/bottom of
 *   the middle)
 *
 * @a: the stack a full with the values
 * @b: the stack b (empty)
 * @arr: array of sorted stack 'a' items
 *
 * Return: nothing
 */
void	sort_stack(t_stack *a, t_stack *b, int *arr)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	if (a->size >= 100)
		j = a->size / 13;
	else
		j = a->size / 6;
	size = a->size;
	while (a->size > 0)
	{
		push_into_b(a, b, arr[i], arr[j]);
		if (i < j)
			i++;
		if (j < size)
			j++;
	}
	restore_to_a(a, b);
	free(arr);
}

/**
 * push_into_b - push items in a into b respcting tha slow/fast algorithm
 *
 * @a: the stack a
 * @b: the stack b
 * @small: the current small target
 * @big: the current big target
 *
 * Return: nothing
 */
void	push_into_b(t_stack *a, t_stack *b, int small, int big)
{
	while (1)
	{
		if (get_value(a->head) <= small)
		{
			push_b(a, b);
			rotate_b(b);
			return ;
		}
		else if (get_value(a->head) <= big)
		{
			push_b(a, b);
			if (b->size > 1 && get_value(b->head) < get_value(b->head->next))
				swap_b(b);
			return ;
		}
		else
			rotate_a(a);
	}
}

/**
 * optimal_push_to_a - push item in a giving index from b
 * into top of a
 *
 * @a: stack a
 * @b: stack b
 * @b_idx: the index where the item located in b which will
 * be moved to a
 *
 * Return: nothing
 */
void	optimal_push_to_a(t_stack *a, t_stack *b, int b_idx)
{
	int	ops;

	ops = calc_ops(b, b_idx);
	while (ops > 0)
	{
		ops--;
		rotate_b(b);
	}
	while (ops < 0)
	{
		ops++;
		rev_rotate_b(b);
	}
	push_a(a, b);
}

/**
 * restore_to_a - resotre all item in b into, by sending the
 * max in b everytime
 *
 * @a: stack a
 * @b: stack a
 *
 * Return: nothing
 */
void	restore_to_a(t_stack *a, t_stack *b)
{
	while (b->size > 0)
		optimal_push_to_a(a, b, bigger_index(b));
}
