/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:00:55 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/27 16:01:22 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size;

	if (old_size < new_size && old_size != 0)
		size = old_size;
	else
		size = new_size;
	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_bzero(new_ptr, new_size);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

int	*allocate_whitespaces(int count, char *error)
{
	int	*ws_array;

	ws_array = (int *)ft_calloc(count + 1, sizeof(int));
	if (!ws_array)
		exit_fail(error);
	ws_array[count] = -9999;
	return (ws_array);
}
