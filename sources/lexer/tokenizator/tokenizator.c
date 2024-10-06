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

char	*extract_token(char **line, int i, int **ws_array, int *token_flag)
{
	char	*start;
	char	*token;
	int		len;

	start = *line;
	len = 0;
	start = getting_start(line, start, &len);
	token = getting_token(start, len);
	while (**line && ft_isspace(**line))
		(*line)++;
	if (!ft_strchr(DELIMS, *token) && *(*line - 1) && !*token_flag
		&& ft_isspace(*(*line - 1)) && i != 0)
	{
		(*ws_array)[i] = 1;
		*token_flag = 0;
	}
	set_token_flag(token, token_flag);
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
	int	in_token;

	in_token = 0;
	while (**line)
	{
		if (ft_strchr(QUOTES, **line))
			in_token = set_quote(line, len, in_token, 's');
		else if (is_delimiter(*line) && in_token != 2)
		{
			if (*len == 0)
				delim_handler(line, len, &in_token, 'g');
			break ;
		}
		else if (!in_token)
			in_token = 1;
		else
		{
			(*len)++;
			(*line)++;
		}
	}
	return (start);
}

void	delim_handler(char **line, int *len, int *in_token, char mode)
{
	char	sign;

	if (in_token && *in_token)
		*in_token = 0;
	if (**line == '|')
	{
		(*len)++;
		(*line)++;
	}
	else if (**line == '<' || **line == '>')
	{
		sign = **line;
		(*len)++;
		(*line)++;
		if (**line && (**line == '<' || **line == '>') && sign == **line)
		{
			if (mode == 'g')
				(*len)++;
			(*line)++;
		}
	}
	else if (ft_isspace(**line))
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
			in_token = set_quote(&line, &count, in_token, 'c');
		else if ((ft_strchr(DELIMS, *line) || ft_isspace(*line))
			&& in_token != 2)
			delim_handler(&line, &count, &in_token, 'c');
		else if (!in_token)
		{
			in_token = 1;
			count++;
		}
		else
			line++;
	}
	return (count);
}
