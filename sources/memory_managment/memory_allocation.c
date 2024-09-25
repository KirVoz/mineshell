/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_allocation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:25:59 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:26:00 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size;

	if (old_size < new_size)
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
	ft_bzero(new_ptr, new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

char	**array_init(void)
{
	char	**empty_array;

	empty_array = (char **)malloc(2 * sizeof(char *));
	if (!empty_array)
		exit_fail("Failed to allocate memory for empty command");
	empty_array[0] = ft_strdup("");
	empty_array[1] = NULL;
	return (empty_array);
}

char	*allocate_string(size_t len, char *error)
{
	char	*result;

	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		exit_fail(error);
	return (result);
}

char	**allocate_array(size_t len, char *error)
{
	char	**result;

	result = (char **)malloc((len + 1) * sizeof(char *));
	if (!result)
		exit_fail(error);
	return (result);
}

void	error_array_allocation(char **result, int i, char *error)
{
	while (i > 0)
		free(result[--i]);
	free(result);
	exit_fail(error);
}
