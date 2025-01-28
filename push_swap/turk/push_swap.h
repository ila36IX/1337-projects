#include "libft/libft.h"
#include "libft/printf/ft_printf.h"

#define PRINT_DEBUG 0

typedef struct t_stack_ {
	t_list *head;
	t_list *tail;
	int size; 
} t_stack;

void push_a(t_stack *stack_a, t_stack *stack_b);
void push_b(t_stack *stack_a, t_stack *stack_b);

void rev_rotate_a(t_stack *a);
void rev_rotate_b(t_stack *b);
void rev_rotate_ab(t_stack *a, t_stack *b);

void rotate_a(t_stack *stack);
void rotate_b(t_stack *stack);
void rotate_ab(t_stack *a, t_stack *b);

void swap_a(t_stack *stack);
void swap_b(t_stack *stack);
void swap_ab(t_stack *a, t_stack *b);

int get_value(t_list *node);
int closest_smaller(t_stack *b, int n);
int smallest_index(t_stack *a);
int bigger_index(t_stack *a);
int closest_bigger(t_stack *a, int n);
void print_ab(t_stack *a, t_stack *b);
int calc_ops(t_stack *stack, int index);
int _abs(int n);
void turk(t_stack *a, t_stack *b);
void sort_stack(t_stack *a, t_stack *b, int *arr);

void execute_ops(t_stack *a, t_stack *b, int a_idx, int b_idx);
