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

char	*quote_counter(char *line)
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
	if (double_quote % 2 != 0)
		return ("\"");
	else if (single_quote % 2 != 0)
		return ("'");
	return (NULL);
}

char	hanging_pipe_heredoc(char *line)
{
	int		valid;
	char	*tmp;

	valid = 0;
	tmp = line;
	while (*line && *line != '|')
	{
		if (!isspace(*line) && *line != '<' && *line != '>')
			valid = 1;
		line++;
	}
	if (ft_strrchr(line, '|') && valid)
	{
		line = ft_strrchr(line, '|') + 1;
		while (*line && isspace(*line))
			line++;
		if (!*line)
			return ('p');
	}
	line = tmp;
	if (ft_strchr(line, '<')
		&& ft_strncmp(ft_strchr(line, '<'), "<<", 2) == 0
		&& ft_strncmp(ft_strchr(line, '<') + 2, "<", 1) != 0)
		return ('h');
	return (0);
}

// void	delete_whitespace_before_token(char **token)
// {
// 	size_t	len;
// 	char	*token_tmp;

// 	len = ft_strlen(*token);
// 	token_tmp = *token;
// 	if ((*token)[len - 1] == ' ')
// 	{
// 		*token = ft_strtrim(*token, " ");
// 		if (!*token)
// 			exit_fail("Token in delete_whitespace");
// 		free(token_tmp);
// 	}
// 	token_tmp = NULL;
// }
