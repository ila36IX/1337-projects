#include "push_swap.h"

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

