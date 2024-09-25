/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:02 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:24:03 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	add_heredocs(t_minishell *minishell, char **tokens, size_t rd)
{
	size_t	i;
	size_t	heredoc_index;
	char	*delimiter;
	char	**heredoc_tokens;

	i = 0;
	heredoc_index = 0;
	minishell->tmp->heredoc_tmp = (char ***)malloc((rd + 1) * sizeof(char **));
	if (!minishell->tmp->heredoc_tmp)
		exit_fail("Failed to allocate memory for heredoc_tmp");
	while (heredoc_index < rd)
	{
		delimiter = find_delimiter(tokens, &i);
		if (!incorrect_delimiter(&delimiter))
		{
			free(minishell->tmp->heredoc_tmp);
			minishell->tmp->heredoc_tmp = NULL;
			return ;
		}
		heredoc_tokens = procees_heredoc_lines(delimiter);
		heredoc_expander(minishell, heredoc_tokens);
		minishell->tmp->heredoc_tmp[heredoc_index] = heredoc_tokens;
		heredoc_index++;
	}
	minishell->tmp->heredoc_tmp[rd] = NULL;
}

char	**handle_heredoc(t_minishell *minishell, char **tokens)
{
	size_t	redirections;

	redirections = redirections_count(tokens);
	if (!redirections)
		return (tokens);
	if (*(tokens + 1))
		add_heredocs(minishell, tokens, redirections);
	return (tokens);
}

char	**handle_pipe(char **tokens)
{
	char	**merged_tokens;
	char	**new_tokens;
	char	*new_line;

	merged_tokens = NULL;
	new_line = readline(PROMPT_HEREDOC);
	new_tokens = tokenizator(new_line);
	merged_tokens = merge_tokens(tokens, new_tokens);
	free(new_line);
	free_tokens(tokens);
	free_tokens(new_tokens);
	return (merged_tokens);
}

char	**pipe_heredoc_main(t_minishell *minishell, char *line)
{
	char	**tokens;

	tokens = tokenizator(line);
	if (hanging_pipe_heredoc(line) == 'h')
		tokens = handle_heredoc(minishell, tokens);
	else if (hanging_pipe_heredoc(line) == 'p')
		tokens = handle_pipe(tokens);
	return (tokens);
}
