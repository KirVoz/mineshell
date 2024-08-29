/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:10:03 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/21 02:22:47 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current -> next != NULL)
		current = current -> next;
	return (current);
}
/*
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
