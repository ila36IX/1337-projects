/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:11:42 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/28 17:22:47 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * arr_to_list - convert array of string into linked list of
 * integers and check with string validations
 *
 * @arr: array of strings (every string is a number or a space
 * sperated numbers)
 * @size: Many strings in the array
 * Return: Pointer to the head of linked list
 */
t_list	*arr_to_list(char **arr, int size)
{
	t_list	*head;
	int		i;

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

/**
 * parse - add integers in string into the end linked list
 * and check if string is valid integer or space seperated
 * integers
 *
 * @head: head of linked list
 * @s: string contains integers
 *
 * Return: 1 if s is valid, and head updated successfully
 * of 0 if error occures
 *
 */
int	parse(char *s, t_list **head)
{
	char	**chunks;

	chunks = ft_split(s, ' ');
	if (!chunks[0])
	{
		free_chunks(chunks);
		return (0);
	}
	return (parse_chunks(chunks, head));
}

/**
 * parse_chunks - add intgers in in chunks into linked list
 *
 * @chunks: array of strings everyone of them contains only
 * integer if valid
 * @head: head of linked list
 *
 * Return: 1 if all strings in chunks are valid strings
 * or 0 if invaliad str is found
 */
int	parse_chunks(char **chunks, t_list **head)
{
	int		i;
	long	n;
	int		*item;

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

/**
 * free_chunks - free array of strings
 *
 * @chunks: array of strings
 * Return: nothing
 */
void	free_chunks(char **chunks)
{
	int	i;

	i = 0;
	while (chunks[i])
		free(chunks[i++]);
	free(chunks[i]);
	free(chunks);
}

int	check_chunck(char *s)
{
	if (!s || !ft_strlen(s))
		return (0);
	if (s[0] == '+' || s[0] == '-')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}
