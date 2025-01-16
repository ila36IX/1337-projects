#include "libft/libft.h"
#include "libft/printf/ft_printf.h"
#include <stdio.h>


#define PRINT_DEBUG 1

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
	return i + 1;
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
t_list *arr_to_list(char **arr, int size)
{
	t_list *head;	
	int *sorted_buff;	
	int *item;	
	int i;

	head = NULL;
	i = 0;
	sorted_buff = ft_calloc(sizeof(int), size);
	if (!sorted_buff)
		return (NULL);
	while (i < size)
	{
		item = ft_calloc(sizeof(int), 1);
		*item = ft_atoi(arr[i]);
		sorted_buff[i] = *item;
		ft_lstadd_back(&head, ft_lstnew(item));
		i++;
	}
	quick_sort(sorted_buff, 0, size - 1);
	normalize_arr(sorted_buff, head, size);
	free(sorted_buff);
	return (head);
}


void print_ints(int *arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
		ft_printf("%d, ", arr[i]);
	ft_printf("      _____\n");
}

typedef struct t_stack_ {
	t_list *head;
	t_list *tail;
	size_t size;
} t_stack;

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
	printf("sa");
}

void swap_b(t_stack *stack)
{
	_swap(stack);
	printf("sb");

}

void swap_ab(t_stack *a, t_stack *b)
{
	_swap(a);
	_swap(b);
	printf("ss");
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
	printf("Pushing %d\n", value);
	while(walk)
	{
		if (!walk->next)
			return (-1);
		printf("is %d between %d and %d?\n", value, get_value(walk), get_value(walk->next));
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
	i = 0;
	while (walk)
	{
		n1 = get_value(walk);
		if (walk->next)
			n2 = get_value(walk->next);
		if (n1 > value && n2 < value)
			return (i);
		walk = walk->next;
		i++;
	}
	return (-1);

}


void best_fit(t_stack *a, t_stack *b)
{
	int value;
	t_list *walk;
	t_list *curr;

	walk = a->head;
	while (walk)
	{
		curr = walk;
		walk = walk->next;
		value = get_value(curr);
		best_push_b(b, value);
	}

}

int main(int ac, char **av)
{		
	t_stack stack_a, stack_b;
	size_t size;
	/*int bits_count;*/

	size = ac - 1;
	stack_a.head = arr_to_list(&av[1], size);;
	stack_a.tail = ft_lstlast(stack_a.head);
	stack_a.size = ft_lstsize(stack_a.head);

	// Empty stack
	stack_b.head = NULL;
	stack_b.tail = NULL;
	stack_b.size = 0;

	print_ab(&stack_a, &stack_b);
	radix(&stack_a, &stack_b);
	print_ab(&stack_a, &stack_b);
	ft_lstclear(&stack_a.head, free);
}
