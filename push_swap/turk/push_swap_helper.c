#include "push_swap.h"

int get_value(t_list *node)
{
	int *content;

	content = node->content;
	return (*content);
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
		return (index - stack->size);
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
