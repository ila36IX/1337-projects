#include "push_swap.h"

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
	ft_printf("sa\n");
}

void swap_b(t_stack *stack)
{
	_swap(stack);
	ft_printf("sb\n");

}

void swap_ab(t_stack *a, t_stack *b)
{
	_swap(a);
	_swap(b);
	ft_printf("ss\n");
}

