/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:42:41 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/23 18:14:09 by aljbari          ###   ########.fr       */
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
