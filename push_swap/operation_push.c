/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:10:27 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/28 16:10:28 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_a(t_stack *stack_a, t_stack *stack_b)
{
	t_list	*tmp;

	if (!stack_b->head)
		return ;
	tmp = stack_b->head;
	stack_b->head = stack_b->head->next;
	(stack_b->size)--;
	tmp->next = stack_a->head;
	stack_a->head = tmp;
	if (!stack_a->tail)
		stack_a->tail = stack_a->head;
	(stack_a->size)++;
	ft_printf("pa\n");
}

void	push_b(t_stack *stack_a, t_stack *stack_b)
{
	t_list	*tmp;

	if (!stack_a->head)
		return ;
	tmp = stack_a->head;
	stack_a->head = stack_a->head->next;
	(stack_a->size)--;
	tmp->next = stack_b->head;
	stack_b->head = tmp;
	if (!stack_b->tail)
		stack_b->tail = stack_b->head;
	(stack_b->size)++;
	ft_printf("pb\n");
}
