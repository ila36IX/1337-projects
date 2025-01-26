#include "libft/printf/ft_printf.h"
#include "push_swap.h"

void restore_to_a(t_stack *a, t_stack *b);
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
                // Swap elements
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

int *sorted_buffer(t_stack *a, t_stack *b)
{
	int *arr;
	t_list *walk;
	int i;
	
	(void) b;

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

int	search_a(t_stack *a, int small, int big);
void sort_stack(t_stack *a, t_stack *b, int *arr)
{
	int i, j, todo;
	int size;

	i = 0;
	if (a->size >= 100)
		j = a->size / 13;
	else
		j = a->size / 7;
	size = a->size;
	while (a->size > 0)
	{
		todo = search_a(a, arr[i], arr[j]);
		push_b(a, b);
		if (todo == 1 && b->size > 1 && get_value(b->head) < get_value(b->head->next))
			swap_b(b);
		if (todo == -1)
			rotate_b(b);
		if (i < j)
			i++;
		if (j < size)
			j++;
	}
	print_ab(a, b);
	restore_to_a(a, b);
}

// 1 swap
// -1 rotate
int	search_a(t_stack *a, int small, int big)
{
	while (1)
	{
		if (get_value(a->head) <= small)
			return (-1);
		else if (get_value(a->head) <= big)
			return (1);
		else
			rotate_a(a);
	}
	return (-2);
}

void optimal_push_to_a(t_stack *a, t_stack *b, int b_idx)
{
	int ops = calc_ops(b, b_idx);

	while (ops > 0)
	{
		ops--;
		rotate_b(b); 
	}
	while (ops < 0)
	{
		ops++;
		rev_rotate_b(b);
	}
	push_a(a, b);
}

void restore_to_a(t_stack *a, t_stack *b)
{
	while (b->size > 0)
	{
		/*execute_ops(a, b, 0, bigger_index(b));*/
		optimal_push_to_a(a, b, bigger_index(b));
		/*push_a(a, b);*/
		ft_printf("1");
	}
}
