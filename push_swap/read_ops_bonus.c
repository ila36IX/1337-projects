/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ops_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 05:04:49 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/11 05:25:20 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"

void	_swap(t_stack *stack);
void	_push_a(t_stack *stack_a, t_stack *stack_b);
void	_push_b(t_stack *stack_a, t_stack *stack_b);
void	_rotate(t_stack *stack);
void	_rev_rotate(t_stack *stack);

void	unknown_op_exit(t_stack *a, t_stack *b, char *line)
{
	ft_lstclear(&a->head, free);
	ft_lstclear(&b->head, free);
	get_next_line(-1);
	ft_putendl_fd("Error", 2);
	free(line);
	exit(EXIT_FAILURE);
}

void	exec_op_extra(t_stack *a, t_stack *b, char *line)
{
	if (ft_strcmp(line, "rra\n") == 0)
		_rev_rotate(a);
	else if (ft_strcmp(line, "rrb\n") == 0)
		_rev_rotate(b);
	else if (ft_strcmp(line, "rrr\n") == 0)
	{
		_rev_rotate(a);
		_rev_rotate(b);
	}
	else
		unknown_op_exit(a, b, line);
}

void	exec_op(t_stack *a, t_stack *b, char *line)
{
	if (ft_strcmp(line, "sa\n") == 0)
		_swap(a);
	else if (ft_strcmp(line, "sb\n") == 0)
		_swap(b);
	else if (ft_strcmp(line, "ss\n") == 0)
	{
		_swap(a);
		_swap(b);
	}
	else if (ft_strcmp(line, "pa\n") == 0)
		_push_a(a, b);
	else if (ft_strcmp(line, "pb\n") == 0)
		_push_b(a, b);
	else if (ft_strcmp(line, "ra\n") == 0)
		_rotate(a);
	else if (ft_strcmp(line, "rb\n") == 0)
		_rotate(b);
	else if (ft_strcmp(line, "rr\n") == 0)
	{
		_rotate(a);
		_rotate(b);
	}
	else
		exec_op_extra(a, b, line);
}

void	read_and_exec_ops(t_stack *a, t_stack *b)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		exec_op(a, b, line);
		free(line);
		line = get_next_line(0);
	}
	if (b->size == 0 && is_sorted(a))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_lstclear(&a->head, free);
	ft_lstclear(&b->head, free);
	exit(0);
}
