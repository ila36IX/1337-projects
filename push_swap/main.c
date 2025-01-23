/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:42:41 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/23 18:06:04 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


t_list *arr_to_list(char **arr, int size)
{
	t_list *head;	
	int *item;	
	int i;

	head = NULL;
	i = 0;
	while (i < size)
	{
		item = ft_calloc(sizeof(int), 1);
		*item = ft_atoi(arr[i]);
		ft_lstadd_back(&head, ft_lstnew(item));
		i++;
	}
	return (head);
}


void print_ints(int *arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
		ft_printf("%d, ", arr[i]);
	ft_printf("      _____\n");
}



void print_ab(t_stack *a, t_stack *b)
{
	if (!PRINT_DEBUG)
		return ;
	t_list *a_walk;
	t_list *b_walk;
	int *a_value;
	int *b_value;

	a_walk = a->head;
	b_walk= b->head;
	while(a_walk || b_walk)
	{
		if (a_walk)
		{
			a_value = a_walk->content;
			ft_printf("%10d", *a_value);
			a_walk = a_walk->next;
		}
		else
			ft_printf("%10s", "_");
		if (b_walk)
		{
			b_value = b_walk->content;
			ft_printf("%10d", *b_value);
			b_walk = b_walk->next;
		}
		else
			ft_printf("%10s", "_");
		ft_printf("\n");

	}
	ft_printf("%10s%10s\n", "---", "---");
	ft_printf("%10s%10s\n\n", "a", "b");
}


int get_value(t_list *node)
{
	int *content;

	content = node->content;
	return (*content);
}


int best_push_b(t_stack *b, int value)
{
	t_list *walk;
	int n1, n2, i;

	walk = b->head;
	if (get_value(walk) < value)
		return (1);
	i = 2;
	while (walk)
	{
		n1 = get_value(walk);
		if (walk->next)
			n2 = get_value(walk->next);
		// printf("(%d %d) ? %d\n", n1, n2, value);
		if (n1 > value && value > n2)
		{
			// printf("Found here %d; size = %d\n", i, b->size);
			if (i > (b->size / 2))
				return (i - b->size - 2);
			return (i);
		}
		walk = walk->next;
		i++;
	}
	return (-1);

}


int closest_smaller(t_stack *b, int n)
{
	t_list *walk;
	int i;
	int closest;
	int closest_index;

	/*printf("Find the [%d] target\n", n);*/
	i = 0;
	closest_index = -1;
	walk = b->head;
	while (walk)
	{
		if (get_value(walk) < n)
		{
			closest_index = i;
			closest = get_value(walk);
			break;
		}
		i++;
		walk = walk->next;
	}
	while (walk)
	{
		if (get_value(walk) < n && n - get_value(walk) < n - closest)
		{
			closest_index = i;
			closest = get_value(walk);
		}
		i++;
		walk = walk->next;
	}
	/*printf("[%d] target is in b[%d]\n", n, closest_index);*/
	return (closest_index);
}

int smallest_index(t_stack *a)
{
	int i;
	int small;
	int small_idx;
	t_list *walk;

	walk = a->head;
	small = get_value(walk);
	small_idx = 0;
	i = 0;
	while (walk)
	{
		if (get_value(walk) < small)
		{
			small = get_value(walk);
			small_idx = i;
		}
		i++;
		walk = walk->next;
	}
	return (small_idx);
}

int bigger_index(t_stack *a)
{
	int i;
	int big;
	int big_idx;
	t_list *walk;

	walk = a->head;
	big = get_value(walk);
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

int closest_bigger(t_stack *a, int n)
{
	t_list *walk;
	int i;
	int closest;
	int closest_index;

	i = 0;
	closest_index = -1;
	walk = a->head;
	while (walk)
	{
		if (get_value(walk) > n)
		{
			closest_index = i;
			closest = get_value(walk);
			break;
		}
		i++;
		walk = walk->next;
	}
	while (walk)
	{
		if (get_value(walk) > n && get_value(walk) - n < closest - n)
		{
			closest_index = i;
			closest = get_value(walk);
		}
		i++;
		walk = walk->next;
	}
	return (closest_index);
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
int calc_ops(t_stack *stack, int index)
{
	if (index > stack->size / 2)
		return -(stack->size - index);
	else
		return (index);
}


/**
 *
 * _abs - absolute value of an integer n
 *
 * @n: integer
 * Return: The absolute value of integer (it's positive version)
 */
int _abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * -1);

}


/**
 *
 * optimized_ops_nbr - calculte the must optimal number of
 * opetations to move two integers from a and b into the top 
 * of there stack
 * @a_idx: index of the first number at stack a
 * @b_idx: index of the second number at stack b
 *
 * Return: The must optimal number of operations
 */
int optimized_ops_nbr(t_stack *a, t_stack *b, int a_idx, int b_idx)
{
	a_idx = calc_ops(a, a_idx);
	b_idx = calc_ops(b, b_idx);

	if (a_idx > 0 && b_idx > 0)
	{
		if (a_idx > b_idx)
			return (b_idx + _abs(a_idx - b_idx));
		else
			return (a_idx + _abs(a_idx - b_idx));
	}
	else if (a_idx < 0 && b_idx < 0)
	{
		if (_abs(a_idx) > _abs(b_idx))
			return (b_idx * -1 + _abs(a_idx - b_idx));
		else
			return (a_idx * -1 + _abs(a_idx - b_idx));
	}
	else
		return (_abs(a_idx) + _abs(b_idx));
}

void excute_without_optimizing(t_stack *a, t_stack *b, int a_ops, int b_ops)
{
	if (a_ops > 0)
		while (a_ops > 0)
		{
			a_ops--;
			rotate_a(a);
		}
	else
		while (a_ops < 0)
		{
			a_ops--;
			rev_rotate_a(a);
		}
	if (b_ops > 0)
		while (b_ops > 0)
		{
			b_ops--;
			rotate_b(b); 
		}
	else
		while (b_ops < 0)
		{
			b_ops++;
			rev_rotate_b(b);
		}
}

void sort3_a(t_stack *a)
{
	int n1;
	int n2;
	int n3;

	if (a->size != 3)
		return ;
	n1 = get_value(a->head);
	n2 = get_value(a->head->next);
	n3 = get_value(a->head->next->next);
	if (n2 > n1 && n2 > n3)
		rev_rotate_a(a);
	if (n1 > n2 && n1 > n3)
		rotate_a(a);
	n1 = get_value(a->head);
	n2 = get_value(a->head->next);
	if (n1 > n2)
		swap_a(a);
}

void execute_ops(t_stack *a, t_stack *b, int a_idx, int b_idx)
{
	int a_ops = calc_ops(a, a_idx);
	int b_ops = calc_ops(b, b_idx);

	if (a_ops > 0 && b_ops > 0)
		while (a_ops > 0 || b_ops > 0)
		{
			if (a_ops > 0 && b_ops > 0)
				rotate_ab(a, b);
			else if (a_ops > 0)
				rotate_a(a);
			else
				rotate_b(b);
			a_ops--;
			b_ops--;
		}
	else if (a_ops < 0 && b_ops < 0)
	{
		a_ops = _abs(a_ops);
		b_ops = _abs(b_ops);
		while (a_ops > 0 || b_ops > 0)
		{
			if (a_ops > 0 && b_ops > 0)
				rev_rotate_ab(a, b);
			else if (a_ops > 0)
				rev_rotate_a(a);
			else
				rev_rotate_b(b);
			a_ops--;
			b_ops--;
		}
	}
	else
		excute_without_optimizing(a, b, a_idx, b_idx);
}

void cheapest_push(t_stack *a, t_stack *b)
{
	t_list *walk;
	int i, j, sum;
	int best_comb[2];

	walk = a->head;
	i = 0;
	sum = a->size + b->size;
	while (walk)
	{
		j = closest_smaller(b, get_value(walk));
		if (j == -1)
			j = bigger_index(b);
		if (optimized_ops_nbr(a, b, i, j) < sum)
		{
			best_comb[0] = i;
			best_comb[1] = j;
			
			sum = optimized_ops_nbr(a, b, i, j);
		}
		if (sum == 0)
			break;
		walk = walk->next;
		i++;
	}
	execute_ops(a, b, best_comb[0], best_comb[1]);
	push_b(a, b);
}

void turk_push_a(t_stack *a, t_stack *b)
{
	t_list *walk;
	int i, j, sum;
	int best_comb[2];

	walk = b->head;
	i = 0;
	sum = a->size + b->size;
	while (walk)
	{
		j = closest_bigger(a, get_value(walk));
		if (j == -1)
			j = smallest_index(a);
		if (optimized_ops_nbr(a, b, j, i) < sum)
		{
			best_comb[0] = j;
			best_comb[1] = i;
			
			sum = optimized_ops_nbr(a, b, j, i);
		}
		if (sum == 0)
			break;
		walk = walk->next;
		i++;
	}
	execute_ops(a, b, best_comb[0], best_comb[1]);
	push_a(a, b);
}

void turk(t_stack *a, t_stack *b)
{
	int i;

	push_b(a,  b);
	push_b(a,  b);
	i = a->size - 3;
	while (i > 0)
	{
		cheapest_push(a, b);
		i--;
	}
	sort3_a(a);
	i = b->size;
	while (i > 0)
	{
		turk_push_a(a, b);
		i--;
	}
	int min_idx = smallest_index(a);
	execute_ops(a, b, min_idx, 0);
}

int main(int ac, char **av)
{		
	t_stack stack_a, stack_b;
	size_t size;

	size = ac - 1;
	stack_a.head = arr_to_list(&av[1], size);;
	stack_a.tail = ft_lstlast(stack_a.head);
	stack_a.size = ft_lstsize(stack_a.head);

	// Empty stack
	stack_b.head = NULL;
	stack_b.tail = NULL;
	stack_b.size = 0;

	print_ab(&stack_a, &stack_b);
	turk(&stack_a, &stack_b);
	print_ab(&stack_a, &stack_b);
	ft_lstclear(&stack_a.head, free);
}
