/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:42:41 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/11 05:24:23 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * bubble_sort - sort the intger in the arr of giving size
 * from smaller to bigger using bubble sort
 *
 * @arr: pointer to a list of integers
 * @size: size of the @arr
 * Return: Nothing, it changes arr
 */
void	bubble_sort(int *arr, int size)
{
	int	swapped;
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		swapped = 0;
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

/**
 * sorted_buffer - generate an array of sorted items
 * from the integers in a giving stack
 *
 * @a: pointer to stack
 * Return: Pointer to list of sorted stack "a" integers
 */
int	*sorted_buffer(t_stack *a)
{
	int		*arr;
	t_list	*walk;
	int		i;

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

/**
 * duplicates_exists - check is array has any equal integer in
 * it
 *
 * @sorted_arr: pointer to list of sorted integers
 * @size: size of @sorted_arr
 * Return: 1 if there are any equal values, or 0 if there are none.
 */
int	duplicates_exists(int *sorted_arr, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (sorted_arr[i - 1] == sorted_arr[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * checkdup_sort - check if "a" contains any duplicates
 * and call sort algo depending on the stack "a" size
 *
 * @a: pointer to stack "a"
 * @b: pointer to stack "b"
 * Return: status value
 */
int	checkdup_sort(t_stack *a, t_stack *b)
{
	int	*sorted;

	sorted = sorted_buffer(a);
	if (duplicates_exists(sorted, a->size))
	{
		ft_lstclear(&a->head, free);
		free(sorted);
		ft_putstr_fd("Error\n", 2);
		return (EXIT_FAILURE);
	}
	free(sorted);
	read_and_exec_ops(a, b);
	ft_lstclear(&a->head, free);
	return (0);
}

/**
 * main - Init two stacks at stack memory, to avoid leaks
 * parse the arguments and check if any invalid chunks exists
 * and call the sort function
 *
 * @av: arguments vectory
 * @ac: arguments count
 * Return: status code
 */
int	main(int ac, char **av)
{
	t_stack	a;
	t_stack	b;
	size_t	size;

	if (ac == 1)
		return (0);
	size = ac - 1;
	a.head = arr_to_list(&av[1], size);
	if (!a.head)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	a.tail = ft_lstlast(a.head);
	a.size = ft_lstsize(a.head);
	b.head = NULL;
	b.tail = NULL;
	b.size = 0;
	return (checkdup_sort(&a, &b));
}
