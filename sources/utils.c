/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:18:04 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:18:05 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_to_lower(char *str)
{
	char	*lower_str;
	int		i;

	lower_str = allocate_dup(str, "Lower_str in str_to_lower");
	i = 0;
	while (lower_str[i])
	{
		lower_str[i] = ft_tolower(lower_str[i]);
		i++;
	}
	return (lower_str);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	print_exit_util(t_minishell *minishell)
{
	printf("PWD environment variable not found\n");
	minishell->exit_code = 1;
}

void	error_free_exit(t_minishell *minishell, char *new_entry)
{
	printf("Memory allocation error\n");
	free(new_entry);
	minishell->exit_code = 1;
}
