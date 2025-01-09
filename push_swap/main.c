#include "libft/libft.h"
#include <bits/types/stack_t.h>
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
	if (!(stack->head) || !(stack->head->next))
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


void bf(t_stack *a, t_stack *b, int i)
{
	t_list *w;	
	int value;
	int a_size = a->size;
	int j = a_size;

	w = a->head;
	// ft_printf("pushing %d to stack b\n", i);
	while (j > 0)
	{
		value = *((int *)(w->content));
		w = w->next;
		if (i == value)
		{
			push_b(a, b);
			print_ab(a, b);
			return ;
		}
		else
			rotate_a(a);
		j--;
		print_ab(a, b);
	}
}

void async_sort(t_stack *a, t_stack *b)
{
	int i;

	i = a->size / 2;

	while (i > 0)
	{
		push_b(a, b);
		i--;
	}
}

void simple_way(t_stack *a, t_stack *b)
{
	int i;
	int size;

	size = a->size;
	i = 0;
	while (i < size)
		bf(a, b, i++);
	i = 0;
	while (i < size)
	{
		push_a(a, b);
		i++;
	}
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

void sorting(t_stack *a, t_stack *b)
{
	int sorted = 0;
	int a_sorted;
	int b_sorted;

	while (sorted)
	{
		if (!a_sorted && !b_sorted)
		{
			if (!is_bigger(a->head, a->head->next) && !is_bigger(b->head, b->head->next))
			{
				swap_a(a);
				(a);
			}
			if (is_bigger(a->head, a->head->next) && is_bigger(b->head, b->head->next))
			{
				rotate_a(a);
			}
			if (is_bigger(a->head, a->head->next) && !is_bigger(b->head, b->head->next))
				rotate_ab(a, b);
		}
		a_sorted = is_sorted19(a);
		b_sorted = is_sorted91(b);
	}
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

	// ft_printf("---------- init ----------\n");
	print_ab(&stack_a, &stack_b);
	// ft_printf("--------------------------\n");

	async_sort(&stack_a, &stack_b);
	ft_printf("[a] sorted? %s\n", is_sorted19(&stack_a) ? "Yes" : "No");

	// ft_printf("---------- after ----------\n");
	print_ab(&stack_a, &stack_b);
	// ft_printf("---------------_-----------\n");
	ft_lstclear(&stack_a.head, free);
}
