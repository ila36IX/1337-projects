/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:13:22 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/28 17:22:48 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * get_value - get integer that node is hoding its pointer
 * Note: Null node will segfault, it must be checked before
 *
 * @node: node in a linked list
 * Return: integer that node is holding
 */
int	get_value(t_list *node)
{
	int	*content;

	content = node->content;
	return (*content);
}

/*
 * calc_ops - Number of operations needed to bring the integer
 * located in giving index to top of stack
 *
 * @stack: the stack which will be changed
 * @index: index of the element that will be moved to top of stack
 *
 * Return: Optimal number of operations
 */
int	calc_ops(t_stack *stack, int index)
{
	if (index > stack->size / 2)
		return (index - stack->size);
	else
		return (index);
}

/**
 * is_sorted - check if stack a is sorted (smaller at top)
 *
 * @a: Pointer to stack
 * Return: 1 is it sorted, 0 if not
 */
int	is_sorted(t_stack *a)
{
	t_list	*walk;

	walk = a->head;
	if (!walk)
		return (1);
	while (walk->next)
	{
		if (get_value(walk) > get_value(walk->next))
			return (0);
		walk = walk->next;
	}
	return (1);
}
