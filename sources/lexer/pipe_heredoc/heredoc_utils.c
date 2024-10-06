/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:23:50 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:23:51 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

char	*find_delimiter(char **tokens, size_t *i)
{
	char	*delimiter;

	delimiter = NULL;
	while (tokens[*i])
	{
		if (strchr(tokens[*i], '<') && (tokens[*i + 1])
			&& ft_strncmp(strchr(tokens[*i], '<'), "<<", 2) == 0)
		{
			*i += 1;
			delimiter = ft_strdup(tokens[*i]);
			if (!delimiter)
				exit_fail("Failed to allocate memory for delimiter");
			break ;
		}
		(*i)++;
	}
	return (delimiter);
}

char	*read_heredoc_lines(char *delimiter)
{
	char	*new_line;

	new_line = readline(PROMPT_HEREDOC);
	if (new_line && ft_strlen(new_line) != 0
		&& ft_strncmp(new_line, delimiter, strlen(new_line)) == 0)
	{
		free(new_line);
		return (NULL);
	}
	return (new_line);
}

char	**procees_heredoc_lines(char *delimiter)
{
	char	**heredoc_tokens;
	size_t	size;
	size_t	capacity;
	char	*new_line;

	capacity = 2;
	heredoc_tokens = allocate_array(capacity - 1, "Procees heredoc lines");
	*heredoc_tokens = NULL;
	size = 0;
	while (1)
	{
		new_line = read_heredoc_lines(delimiter);
		if (!new_line)
			break ;
		add_line_to_heredoc(&heredoc_tokens, &size, &capacity, new_line);
		free(new_line);
	}
	heredoc_tokens[size] = NULL;
	free(delimiter);
	delimiter = NULL;
	return (heredoc_tokens);
}

void	add_line_to_heredoc(char ***heredoc_tokens, size_t *size,
		size_t *capacity, char *line)
{
	size_t	old_capacity;

	old_capacity = *capacity;
	if (*size == *capacity - 1)
	{
		(*capacity) *= 2;
		*heredoc_tokens = (char **)ft_realloc(*heredoc_tokens, old_capacity
				* sizeof(char *), *capacity * sizeof(char *));
		if (!*heredoc_tokens)
			exit_fail("Failed to reallocate memory for heredoc tokens");
	}
	(*heredoc_tokens)[(*size)++] = ft_strdup(line);
	if (!(*heredoc_tokens)[*size - 1])
		exit_fail("Failed to allocate memory for heredoc tokens");
}
