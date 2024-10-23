/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:01:16 by aaleksee          #+#    #+#             */
/*   Updated: 2024/10/12 11:01:17 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	should_merge(char **tokens, int i, int *ws_tmp)
{
	if (tokens[i] && tokens[i + 1] && !is_valid_token(tokens[i])
		&& ft_strncmp(tokens[i], "|", ft_strlen(tokens[i])) != 0
		&& (i == 0
			|| ft_strncmp(tokens[i - 1], "|", ft_strlen(tokens[i - 1])) != 0)
		&& ft_strncmp(tokens[i + 1], "|", ft_strlen(tokens[i + 1])) != 0
		&& ws_tmp[i] == 0 && *(tokens[i]) != '-')
		return (1);
	return (0);
}

void	merge_token(char **tokens, int *ws_tmp, int i)
{
	char	*tmp;
	int		j;

	tmp = tokens[i];
	tokens[i] = ft_strjoin(tokens[i], tokens[i + 1]);
	free(tmp);
	free(tokens[i + 1]);
	ws_tmp[i] = ws_tmp[i + 1];
	j = i + 1;
	while (tokens[j + 1])
	{
		tokens[j] = tokens[j + 1];
		ws_tmp[j] = ws_tmp[j + 1];
		j++;
	}
	tokens[j] = NULL;
	ws_tmp[j] = 0;
}

int	handle_merge(char **tokens, int *ws_tmp, int i, int j)
{
	while (tokens[i + 1] && should_merge(tokens, i, ws_tmp))
		merge_token(tokens, ws_tmp, i);
	if (i != j)
	{
		tokens[j] = tokens[i];
		ws_tmp[j] = ws_tmp[i];
	}
	return (j + 1);
}

void	merger_main(t_minishell *minishell, char **tokens)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (tokens[i])
	{
		if (should_merge(tokens, i, minishell->tmp->ws_tmp))
			j = handle_merge(tokens, minishell->tmp->ws_tmp, i, j);
		else
		{
			if (i != j)
			{
				tokens[j] = tokens[i];
				minishell->tmp->ws_tmp[j] = minishell->tmp->ws_tmp[i];
			}
			j++;
		}
		i++;
	}
	tokens[j] = NULL;
	minishell->tmp->ws_tmp[j] = 0;
}
