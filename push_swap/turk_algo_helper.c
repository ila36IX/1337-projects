#include "push_swap.h"

int closest_smaller(t_stack *b, int n)
{
	t_list *walk;
	int i;
	int closest;
	int closest_index;

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
