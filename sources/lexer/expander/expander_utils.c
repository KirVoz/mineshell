/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:54 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:24:55 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	expand_to_env(t_minishell *minishell, char **cur_ptr, char cur_quote)
{
	char	*env_value;

	env_value = get_env_value(minishell, cur_ptr);
	if (env_value || cur_quote == '"')
	{
		free(env_value);
		return (1);
	}
	return (0);
}

char	*allocate_dup(char *dup, char *error)
{
	char	*result;

	result = ft_strdup(dup);
	if (!result)
		exit_fail(error);
	return (result);
}

void	write_exit_code(char **result, char *exit_code, int *i)
{
	while (*exit_code)
	{
		(*result)[*i] = *exit_code;
		(*i)++;
		exit_code++;
	}
}
