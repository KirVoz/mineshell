/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:10 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:24:11 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

size_t	redirections_count(char **tokens)
{
	size_t	i;
	size_t	redirections;

	i = 0;
	redirections = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '<') && ft_strncmp(strchr(tokens[i], '<'),
				"<<", 2) == 0)
			redirections++;
		i++;
	}
	return (redirections);
}

char	**get_valid_tokens(void)
{
	char	**tokens;

	tokens = allocate_array(5, "Get valid tokens");
	tokens[0] = "<";
	tokens[1] = ">";
	tokens[2] = "<<";
	tokens[3] = ">>";
	tokens[4] = "|";
	tokens[5] = NULL;
	return (tokens);
}

int	incorrect_delimiter(char **delimiter)
{
	char	**tokens;
	int		i;

	if (!*delimiter)
		return (0);
	tokens = get_valid_tokens();
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(*delimiter, tokens[i], ft_strlen(tokens[i])) == 0)
		{
			free(*delimiter);
			free(tokens);
			*delimiter = NULL;
			tokens = NULL;
			return (0);
		}
		i++;
	}
	free(tokens);
	return (1);
}
