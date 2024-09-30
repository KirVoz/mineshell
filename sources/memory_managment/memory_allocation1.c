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

char	*allocate_dup(char *dup, char *error)
{
	char	*result;

	result = ft_strdup(dup);
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
