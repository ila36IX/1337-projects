#include "push_swap.h"

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
			a_ops++;
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
		excute_without_optimizing(a, b, a_ops, b_ops);
}

void turk_push_b(t_stack *a, t_stack *b)
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
		turk_push_b(a, b);
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
