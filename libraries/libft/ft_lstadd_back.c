/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:28:05 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/21 02:20:14 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (current -> next != NULL)
		current = current -> next;
	current -> next = new;
}
/*
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
	int iTest = 1;
	t_list *l =  NULL;
	ft_lstadd_back(&l, ft_lstnew((void*)1));
	ft_lstadd_back(&l, ft_lstnew((void*)2));
}

#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

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
	printf("%s", (char *)(ft_lstlast(current) -> content));
	while (current != NULL) 
	{
		t_list *next = current->next; 
		free(current);
		current = next;
	}
}
*/
