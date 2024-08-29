/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:13:39 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/19 19:14:08 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	current = lst;
	new = NULL;
	while (current != NULL)
	{
		tmp = ft_lstnew((*f)(current -> content));
		if (!tmp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, tmp);
		current = current -> next;
	}
	return (new);
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

#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

void ft_lstadd_back(t_list **lst, t_list *new)
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

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !(*lst))
		return ;
	current = *lst; 
	while (current != NULL) 
	{
		 if (del != NULL)
            del(current->content);
		next = current->next;
		free(current);
		current = next;
	}	
	*lst = NULL;
}

#include <stdio.h>

void	*addOne(void * p) 
{
	void *r = malloc(sizeof(int)); 
	*(int *)r = *(int *)p + 1;
	return (r);
	}

int	main()
{
	int tab[] = {0, 1, 2, 3};
	t_list *l =  ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
		ft_lstadd_back(&l, ft_lstnew(tab + i));
	t_list * m = ft_lstmap(l, addOne, free);
	t_list * tmp = l;
	for (int i = 0; i < 4; ++i)
	{
		printf("%d\n", *(int *)tmp->content); // == i
		tmp = (t_list *)tmp->next;
	}
	tmp = m;
	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", *(int *)tmp->content); // == i + 1 
		tmp = (t_list *)tmp->next;
	}
	ft_lstclear(&m, free);
	write(1, "\n", 1);
}
*/