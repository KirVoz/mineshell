/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:53:12 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/21 02:21:35 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
