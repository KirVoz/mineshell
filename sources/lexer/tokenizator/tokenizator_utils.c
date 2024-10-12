/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:23:31 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:23:33 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	set_quote(char **line, int *count, int in_token, char mode)
{
	static char	quote;

	if (quote == 0)
		quote = **line;
	if (in_token != 2)
	{
		(*count)++;
		in_token = 2;
	}
	else if (in_token == 2 && **line == quote)
	{
		in_token = 0;
		quote = 0;
		if (mode == 's')
			(*count)++;
	}
	else if (mode == 's')
		(*count)++;
	(*line)++;
	return (in_token);
}

void	increment_len_line(char ***line, int **len)
{
	(**len)++;
	(**line)++;
}

int	is_delimiter(char *line)
{
	if (ft_isspace(*line) || ft_strchr(DELIMS, *line) != NULL || ((*line == '<'
				|| *line == '>') && *(line + 1) == *line))
		return (1);
	return (0);
}

void	set_token_flag(char *token, int *flag)
{
	if (ft_strchr("|", *token))
		*flag = 1;
	else
		*flag = 0;
}
