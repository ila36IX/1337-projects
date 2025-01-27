#include "push_swap.h"

t_list *arr_to_list(char **arr, int size)
{
	t_list *head;	
	int i;

	head = NULL;
	i = 0;
	while (i < size)
	{
		if (!parse(arr[i], &head))
		{
			ft_lstclear(&head, free);
			return (NULL);
		}
		i++;
	}
	return (head);
}

int	parse(char *s, t_list **head)
{
	char **chunks;

	chunks = ft_split(s, ' ');
	if (!chunks[0])
	{
		free_chunks(chunks);
		return (0);
	}
	return (parse_chunks(chunks, head));
}
#include <stdio.h>
int parse_chunks(char **chunks, t_list **head)
{
	int i;
	long	n;
	int *item;

	i = 0;
	while (chunks[i])
	{
		if (!check_chunck(chunks[i]))
		{
			free_chunks(chunks);
			return (0);
		}
		item = ft_calloc(sizeof(int), 1);
		n = ft_atol(chunks[i]);
		if (n > (long)INT_MAX || n < (long)INT_MIN)
		{
			free_chunks(chunks);
			return (0);
		}
		*item = n;
		ft_lstadd_back(head, ft_lstnew(item));
		i++;
	}
	free_chunks(chunks);
	return (1);
}

void free_chunks(char **chunks)
{
	int i;

	i = 0;
	while  (chunks[i])
		free(chunks[i++]);
	free(chunks[i]);
	free(chunks);
}

int check_chunck(char *s)
{
	while (*s)
	{
		if (*s != '-' && *s != '+' && !ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}



