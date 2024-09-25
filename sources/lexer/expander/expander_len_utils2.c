/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_len_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 07:43:04 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 07:43:05 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

size_t	count_to_dollar(char **line)
{
	size_t	len;

	len = 0;
	while (**line && **line != '$')
	{
		len++;
		(*line)++;
	}
	return (len);
}

size_t	exit_len(char *token, char *exit_code)
{
	size_t	len;

	len = 0;
	while (*token)
	{
		if (*token == '$' && *(token + 1) && *(token + 1) == '?')
		{
			len += ft_strlen(exit_code);
			token++;
		}
		else if (*token != '"')
			len++;
		token++;
	}
	return (len);
}
