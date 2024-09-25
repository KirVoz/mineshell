/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:23:18 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:23:23 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

char	*extract_token(char **line, int i, int *token_flag)
{
	char	*start;
	char	*token;
	char	*token_tmp;
	int		len;

	start = *line;
	len = 0;
	start = getting_start(line, start, &len);
	token = getting_token(start, len);
	while (**line && **line == ' ')
		(*line)++;
	if (!ft_strchr(DELIMS, *token) && *(*line - 1) && !*token_flag
		&& *(*line - 1) == ' ' && i != 0)
	{
		token_tmp = token;
		token = ft_strjoin(token, " ");
		if (!token)
			exit_fail("Tokens in extract_token");
		free(token_tmp);
		token_flag = 0;
	}
	set_token_flag(token, token_flag);
	token_tmp = NULL;
	return (token);
}

char	*getting_token(char *start, int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	return (token);
}

char	*getting_start(char **line, char *start, int *len)
{
	while (*line)
	{
		if (ft_strchr(QUOTES, **line))
		{
			if (*len == 0)
				*line = find_end_quote_len(*line, len);
			break ;
		}
		else if (is_delimiter(*line))
		{
			if (*len == 0)
				redirection_handle(line, len, NULL);
			break ;
		}
		(*len)++;
		(*line)++;
	}
	return (start);
}

void	redirection_handle(char **line, int *count, int *in_token)
{
	if (in_token && *in_token)
		*in_token = 0;
	if (**line == '|')
	{
		(*count)++;
		(*line)++;
	}
	else if (**line == '<' || **line == '>')
	{
		(*count)++;
		(*line)++;
		if (**line && (**line == '<' || **line == '>'))
		{
			(*line)++;
			if (!in_token)
				(*count)++;
		}
	}
	else if (**line == ' ')
		(*line)++;
}

int	count_tokens(char *line)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*line)
	{
		if (ft_strchr(QUOTES, *line))
		{
			line = find_end_quote(line, &count);
			in_token = 0;
		}
		else if (is_delimiter(line))
			redirection_handle(&line, &count, &in_token);
		else if (!in_token)
		{
			in_token = 1;
			count++;
		}
		else if (*line && !is_delimiter(line))
			line++;
	}
	return (count);
}
