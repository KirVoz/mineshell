/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:17 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:24:18 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

char	**merge_tokens(char **tokens, char **new_tokens)
{
	char	**result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = allocate_array(array_len(tokens) + array_len(new_tokens),
			"Result in merge_tokens");
	while (tokens[i])
	{
		result[i] = ft_strdup(tokens[i]);
		if (!result[i])
			error_array_allocation(result, i, "Result[i] in merge_tokens");
		i++;
	}
	while (new_tokens[j])
	{
		result[i] = ft_strdup(new_tokens[j]);
		if (!result[i])
			error_array_allocation(result, i, "Result[i] in merge_tokens");
		i++;
		j++;
	}
	result[i] = NULL;
	return (result);
}

int	*merge_ws(int *ws, int *ws_pipe)
{
	int		*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = allocate_whitespaces(int_array_len(ws) + int_array_len(ws_pipe),
			"Result in merge_ws");
	while (ws[i])
	{
		result[j] = ws[i];
		i++;
		j++;
	}
	i = 0;
	while (ws_pipe[i])
	{
		result[j] = ws_pipe[i];
		i++;
		j++;
	}
	result[j] = 0;
	free(ws);
	return (result);
}
