/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:22:38 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:22:42 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	quote_counter(t_minishell *minishell, char *line)
{
	int		double_quote;
	int		single_quote;

	double_quote = 0;
	single_quote = 0;
	while (*line)
	{
		if (*line == '\"' && !single_quote)
			double_quote = !double_quote;
		else if (*line == '\'' && !double_quote)
			single_quote = !single_quote;
		line++;
	}
	if (double_quote % 2 != 0 || single_quote % 2 != 0)
	{
		free(minishell->tmp->line);
		if (double_quote % 2 != 0)
			return (syntax_error(minishell, "\""));
		else if (single_quote % 2 != 0)
			return (syntax_error(minishell, "'"));
	}
	return (1);
}

char	heredoc_check(char *line, char pipe_heredoc)
{
	while (ft_strchr(line, '<') && *(ft_strchr(line, '<') + 1))
	{
		if (ft_strncmp(ft_strchr(line, '<'), "<<", 2) == 0
			&& ft_strncmp(ft_strchr(line, '<') + 2, "<", 1) != 0)
		{
			if (pipe_heredoc == 0)
				return ('h');
			return ('b');
		}
		line = ft_strchr(line, '<') + 1;
	}
	return (0);
}

char	hanging_pipe_heredoc(char *line)
{
	char	*tmp;
	char	pipe_heredoc;
	int		valid;

	tmp = line;
	pipe_heredoc = 0;
	valid = 0;
	while (*line && ft_strrchr(line, '|') && *line != '|')
	{
		if (!isspace(*line) && *line != '<' && *line != '>')
			valid = 1;
		line++;
	}
	if (ft_strrchr(line, '|') && valid)
	{
		line = ft_strrchr(line, '|') + 1;
		while (*(line - 2) != '|' && *line && isspace(*line))
			line++;
		if (!*line && *(line - 2) != '|')
			pipe_heredoc = 'p';
	}
	line = tmp;
	pipe_heredoc = heredoc_check(line, pipe_heredoc);
	return (pipe_heredoc);
}
