#include "push_swap.h"

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
	ft_printf("ra\n");
}

void rotate_b(t_stack *stack)
{
	_rotate(stack);
	ft_printf("rb\n");
}

void rotate_ab(t_stack *a, t_stack *b)
{
	_rotate(a);
	_rotate(b);
	ft_printf("rr\n");
}
