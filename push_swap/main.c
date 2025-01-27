/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:42:41 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/27 01:25:37 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/printf/ft_printf.h"
#include "push_swap.h"

void bubble_sort(int *arr, int size)
{
	int swapped;
	int i = 0;

	while (i < size - 1)
	{
		swapped = 0;
		int j = 0;

		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break;
		i++;
	}
}

int *sorted_buffer(t_stack *a)
{
	int *arr;
	t_list *walk;
	int i;

	arr = ft_calloc(a->size, sizeof(int));
	i = 0;
	walk = a->head;
	while (walk)
	{
		arr[i++] = get_value(walk);
		walk = walk->next;
	}
	bubble_sort(arr, a->size);
	return (arr);
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

int check_duplicates(int *sorted_arr, int size)
{
	int i;

	i = 1;
	while  (i < size)
	{
		if (sorted_arr[i - 1] == sorted_arr[i])
			return (0);
		i++;
	}
	return (1);
}

int main(int ac, char **av)
{		
	t_stack a, b;
	size_t size;
	int *sorted;

	size = ac - 1;
	a.head = arr_to_list(&av[1], size);;
	if (!a.head)
	{
		ft_printf("Error\n");
		return (0);
	}
	sorted = sorted_buffer(&a);
	if (check_duplicates(sorted, a.size))
	{
		// TODO: Look for duplicated and free sorted array if any found
	}
	a.tail = ft_lstlast(a.head);
	a.size = ft_lstsize(a.head);
	b.head = NULL;
	b.tail = NULL;
	b.size = 0;
	print_ab(&a, &b);
	sort_stack(&a, &b, sorted);
	print_ab(&a, &b);
	ft_lstclear(&a.head, free);
}
