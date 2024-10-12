/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_len_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:30:51 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:30:52 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

size_t	expanded_line_len(t_minishell *minishell,
		char *token, char *current_quote)
{
	size_t	len;
	char	*env_value;

	len = 0;
	while (*token)
	{
		set_current_quote(current_quote, *token, &token);
		if (*token == '$' && *(token + 1) && (ft_isalnum(*(token + 1))
				|| *(token + 1) == '_') && *current_quote != '\'')
		{
			env_value = get_env_value(minishell, &token);
			len += ft_strlen(env_value);
			free(env_value);
			continue ;
		}
		else if (*token != *current_quote)
		{
			token++;
			len++;
		}
		else if (*token && *token == *current_quote)
			token++;
	}
	return (len);
}

size_t	exit_len(char *token, char *exit_code)
{
	size_t	len;
	char	current_quote;

	len = 0;
	current_quote = 0;
	while (*token)
	{
		set_current_quote_question(&current_quote, *token);
		if (*token && *token == '$' && *(token + 1) && *(token + 1) == '?'
			&& current_quote != '\'')
		{
			len += ft_strlen(exit_code);
			token++;
		}
		if (*token)
		{
			token++;
			len++;
		}
	}
	return (len);
}

size_t	exit_len_hd(char *token, char *exit_code)
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
		else if (*token)
			len++;
		token++;
	}
	return (len);
}
