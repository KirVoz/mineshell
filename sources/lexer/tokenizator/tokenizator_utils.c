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

char	*find_end_quote(char *line, int *count)
{
	char	quote;
	int		i;

	quote = *line;
	i = 1;
	while (line[i] && line[i] != quote)
		i++;
	if (count)
		(*count)++;
	return (&(line[i + 1]));
}

char	*find_end_quote_len(char *line, int *len)
{
	int		i;
	char	quote;

	i = 1;
	quote = *line;
	while (line[i] && line[i] != quote)
	{
		i++;
		(*len)++;
	}
	*len += 2;
	return (&(line[i + 1]));
}

int	find_quotation_len(char *line)
{
	char	quote;
	int		i;

	quote = *line;
	i = 1;
	while (line[i] && line[i] != quote)
		i++;
	return (i + 1);
}

int	is_delimiter(char *line)
{
	if (*line == ' ' || ft_strchr(DELIMS, *line) != NULL || ((*line == '<'
				|| *line == '>') && *(line + 1) == *line))
		return (1);
	return (0);
}

void	set_token_flag(char *token, int *flag)
{
	if (ft_strchr(DELIMS, *token))
		*flag = 1;
}
