/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:23:16 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/11 05:16:04 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"
# include "libft/printf/ft_printf.h"

typedef struct t_stack_
{
	t_list	*head;
	t_list	*tail;
	int		size;
}			t_stack;

void		push_a(t_stack *stack_a, t_stack *stack_b);
void		push_b(t_stack *stack_a, t_stack *stack_b);

void		rev_rotate_a(t_stack *a);
void		rev_rotate_b(t_stack *b);
void		rev_rotate_ab(t_stack *a, t_stack *b);

void		rotate_a(t_stack *stack);
void		rotate_b(t_stack *stack);
void		rotate_ab(t_stack *a, t_stack *b);

void		swap_a(t_stack *stack);
void		swap_b(t_stack *stack);
void		swap_ab(t_stack *a, t_stack *b);

int			get_value(t_list *node);
int			bigger_index(t_stack *a);
void		print_ab(t_stack *a, t_stack *b);
int			calc_ops(t_stack *stack, int index);
void		sort_stack(t_stack *a, t_stack *b, int *arr);
void		restore_to_a(t_stack *a, t_stack *b);
void		push_into_b(t_stack *a, t_stack *b, int small, int big);

/* Parsers */
long		ft_atol(const char *str);
t_list		*arr_to_list(char **arr, int size);
void		free_chunks(char **chunks);
int			check_chunck(char *s);
int			parse_chunks(char **chunks, t_list **head);
int			parse(char *s, t_list **head);

int			is_sorted(t_stack *a);
void		sm_sort(t_stack *a, t_stack *b);

/* bonus */
void		read_and_exec_ops(t_stack *a, t_stack *b);

#endif
