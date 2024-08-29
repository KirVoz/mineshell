/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:03:12 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/17 20:03:14 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*current;

	len = 0;
	current = lst;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	return (len);
}
/*
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

#include <stdio.h>
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node -> content = content;
	node -> next = NULL;
	return (node);
}

int main()
{
	t_list *a = ft_lstnew("Hello");
	t_list *b = ft_lstnew("World");
	t_list *c = ft_lstnew("Nope");
	
	ft_lstadd_front(&a, b);
	ft_lstadd_front(&b, c);
	t_list *current = c; 
	while (current != NULL) 
	{
    	printf("%s\n", (char *)(current -> content));
		printf("%p \n", current -> next);
    	current = current -> next;
	}
	current = c; 
	printf("%d\n", ft_lstsize(c));
	while (current != NULL) 
	{
		t_list *next = current -> next; 
		free(current);
		current = next;
	}
}
*/