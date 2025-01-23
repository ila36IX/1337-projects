/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:42:41 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/23 17:22:47 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/printf/ft_printf.h"
#include <bits/types/stack_t.h>
#include <stdio.h>


#define PRINT_DEBUG 0
typedef struct t_stack_ {
	t_list *head;
	t_list *tail;
	int size; 
} t_stack;

void print_ints(int *arr, size_t size);
void swap(int* a, int* b);

int partition(int *arr, int low, int high)
{
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);  
	return (i + 1);
}

void quick_sort(int *arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/**
 * get_index - Use binary search to find the index of the x in
 * sorted array
 *
 * @sorted_arr: array of sorted integers
 * @x: value to find
 * @size: size of the array
 *
 * Return: index of x in soreted_arr or -1 if not found
 */
int get_index(int *sorted_arr, int x, size_t size)
{
	int low;
	int high;
	int mid;

	low = 0;
	high = size - 1;

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (sorted_arr[mid] == x)
			return mid;
		if (sorted_arr[mid] < x)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (-1);
}


/**
 * normalize_stack - replace every integer with its order in the array
 * eg. 69->6->9 will be 2->0->1
 *
 * @sorted_arr: array of sorted integers
 * @head: the stack that will be normalized
 * @size: number of items in the stack
 *
 * Return: Nothing.
 */
void normalize_arr(int *sorted_arr, t_list *head, size_t size)
{
	int *item;

	while (head)
	{
		item = head->content;
		*item = get_index(sorted_arr, *item, size);
		head = head->next;
	}
}


void print_arr(t_list *head)
{
	int *item;

	while (head)
	{
		item = head->content;
		ft_printf("%10d\n", *item);
		head = head->next;
	}
	ft_printf("---\n");
}

/**
 *  arr_to_stack - Convert array of integers into a linked list of consecutive
 *  integers starting form 0, each number in the linked list represents the
 *  actual order of the original
 *
 * @arr: array of strings of integers (must be checked before calling this function)
 * - it's important for the items to be unique, and represent a valid integer
 * @size: the size of array
 *
 * Return: Pointer to the head of the array, must be free later
 */ 
/*t_list *arr_to_list(char **arr, int size)*/
/*{*/
/*	t_list *head;	*/
/*	int *sorted_buff;	*/
/*	int *item;	*/
/*	int i;*/
/**/
/*	head = NULL;*/
/*	i = 0;*/
/*	sorted_buff = ft_calloc(sizeof(int), size);*/
/*	if (!sorted_buff)*/
/*		return (NULL);*/
/*	while (i < size)*/
/*	{*/
/*		item = ft_calloc(sizeof(int), 1);*/
/*		*item = ft_atoi(arr[i]);*/
/*		sorted_buff[i] = *item;*/
/*		ft_lstadd_back(&head, ft_lstnew(item));*/
/*		i++;*/
/*	}*/
/*	quick_sort(sorted_buff, 0, size - 1);*/
/*	normalize_arr(sorted_buff, head, size);*/
/*	free(sorted_buff);*/
/*	return (head);*/
/*}*/
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


void push_a(t_stack *stack_a, t_stack *stack_b)
{
	t_list *tmp;

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
	printf("pa\n");
}

void push_b(t_stack *stack_a, t_stack *stack_b)
{
	t_list *tmp;

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
	printf("pb\n");
}

void _swap(t_stack *stack)
{
	int *temp;
	
	if (!(stack->head) || !(stack->head->next))
		return ;
	temp = stack->head->content;
	stack->head->content = stack->head->next->content;
	stack->head->next->content = temp;

}
void swap_a(t_stack *stack)
{
	_swap(stack);
	printf("sa\n");
}

void swap_b(t_stack *stack)
{
	_swap(stack);
	printf("sb\n");

}

void swap_ab(t_stack *a, t_stack *b)
{
	_swap(a);
	_swap(b);
	printf("ss\n");
}

void _rotate(t_stack *stack)
{
	t_list *prv_head;

	if (!(stack->tail) || (stack->tail == stack->head))
		return ;
	prv_head = stack->head;
	stack->tail->next = prv_head;
	stack->head = stack->head->next;
	stack->tail = prv_head;
	stack->tail->next = NULL;
}

void rotate_a(t_stack *stack)
{
	_rotate(stack);
	printf("ra\n");
}

void rotate_b(t_stack *stack)
{
	_rotate(stack);
	printf("rb\n");
}

void rotate_ab(t_stack *a, t_stack *b)
{
	_rotate(a);
	_rotate(b);
	printf("rr\n");
}

void _rev_rotate(t_stack *stack)
{
    t_list *new_head;
    
    if (!(stack->head) || !(stack->head->next))
        return;
    if (!(stack->tail))
        return;
    new_head = stack->tail;
    t_list *current = stack->head;
    while (current->next != stack->tail)
        current = current->next;
    new_head->next = stack->head;    
    stack->head = new_head;          
    stack->tail = current;           
    stack->tail->next = NULL;       
}

void rev_rotate_a(t_stack *a)
{
	_rev_rotate(a);
	ft_printf("rra\n");
}

void rev_rotate_b(t_stack *b)
{
	_rev_rotate(b);
	ft_printf("rrb\n");
}

void rev_rotate_ab(t_stack *a, t_stack *b)
{
	_rev_rotate(a);
	_rev_rotate(b);
	ft_printf("rrr\n");
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


int	is_sorted19(t_stack *stack)
{
	t_list *walk;

	walk = stack->head;
	while (walk)
	{
		if (walk->next && *(int *)(walk->content) > *(int *)(walk->next->content))
			return (0);
		walk = walk->next;
	}
	return (1);
}

int	is_sorted91(t_stack *stack)
{
	t_list *walk;

	walk = stack->head;
	while (walk)
	{
		if (walk->next && *(int *)(walk->content) < *(int *)(walk->next->content))
			return (0);
		walk = walk->next;
	}
	return (1);
}

int is_bigger(t_list *a, t_list *b)
{
	int *v1;
	int *v2;

	v1 = a->content;
	v2 = b->content;
	if (*v1 > *v2)
		return (1);
	return (0);
}

int get_max_bits(t_stack *stack)
{
	int max;
	int max_bits;

	max = stack->size - 1;
	max_bits = 0;
	while(max > 0)
	{
		max >>= 1;
		max_bits++;
	}
	return (max_bits);
}

int get_bit(int value, int index)
{
	 return ((value >> index) & 1);
}

int get_value(t_list *node)
{
	int *content;

	content = node->content;
	return (*content);
}


int many_operations(t_stack *b, int value)
{
	t_list *walk;
	int i;

	walk = b->head;
	if (get_value(walk) > value)
		return (1);
	i = 1;
	/*printf("Pushing %d\n", value);*/
	while(walk)
	{
		if (!walk->next)
			return (-1);
		/*printf("is %d between %d and %d?\n", value, get_value(walk), get_value(walk->next));*/
		if (get_value(walk) < value && get_value(walk->next) > value)
				return (i);
		i++;
		walk = walk->next;
	}
	return (i);

}

/**
 * radix_move - all integets with 0 in i-th bit will be moves to b
 * and the one with 1 will remain in a
 *
 * @a: stack a, in the end will contain all the integers with bit
 * in  @bit_index = 1
 * @b: stack b: in the end will contain all the integers with bit
 * in @bit_index = 0
 *
 * Return: Nothing
 */
void radix_move(t_stack *a, t_stack *b, int bit_index)
{
	t_list *walk, *curr_node;
	int i;
	int stack_size;

	walk = a->head;
	i = 0;
	stack_size = a->size;
	while (i < stack_size && walk)
	{
		curr_node = walk;
		walk = walk->next;
		if ((get_bit(get_value(curr_node), bit_index) == 0))
			push_b(a, b);
		else
			rotate_a(a);
		i++;
	}
}

void push_all_b_to_a(t_stack *a, t_stack *b)
{
	int i;
	int stack_size;

	i = 0;
	stack_size = b->size;
	while (i < stack_size)
	{
		push_a(a, b);
		i++;
	}

}

void radix_step(t_stack *a, t_stack *b, int i)
{
	// update needed
	radix_move(a, b, i);
	print_ab(a, b);
	push_all_b_to_a(a, b);
	print_ab(a, b);
}

void radix(t_stack *a, t_stack *b)
{
	int bits_count = get_max_bits(a);
	int i = 0;

	while (i < bits_count)
	{
		radix_step(a, b, i);
		print_ab(a, b);
		i++;
	}

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
	/*printf("target of %d is in a[%d]\n", n, closest_index);*/
	return (closest_index);
}

/*
 * How many operations needed to bring the integer
 * located in giving index to top of a
 */
int calc_ops(t_stack *a, int index)
{
	if (index > a->size / 2)
		return -(a->size - index);
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
			b_ops--; rotate_b(b); } else
		while (b_ops < 0)
		{
			b_ops++;
			rev_rotate_b(a);
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
		{
			j = bigger_index(b);
			/*printf("bigger: %d\n", j);*/
		}
		/*printf("a(i) = %d, b(i) = %d\n", i, j);*/
		if (optimized_ops_nbr(a, b, i, j) < sum)
		{
			best_comb[0] = i;
			best_comb[1] = j;
			
			sum = optimized_ops_nbr(a, b, i, j);
			/*printf("{new best} a(i) = %d, b(i) = %d\n", i, j);*/
		}
		if (sum == 0)
			break;
		walk = walk->next;
		i++;
	}
	/*printf("rev a: %d | rev b: %d\n", best_comb[0], best_comb[1]);*/
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
			
			// printf("{new best} a(i) = %d, b(i) = %d\n", j, i);
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
	/*cheapest_push(a, b);*/
	/*print_ab(a, b);*/
	/*cheapest_push(a, b);*/
	/*print_ab(a, b);*/
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
