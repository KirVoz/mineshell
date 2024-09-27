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

size_t	expanded_line_len(t_minishell *minishell, char *token)
{
	size_t	len;
	char	*env_value;

	len = 0;
	while (*token)
	{
		if (*token == '$' && *(token + 1) && *(token + 1) != '$')
		{
			env_value = get_env_value(minishell, &token);
			len += ft_strlen(env_value);
			if (len == 0 && *token == ' ')
				len--;
			free(env_value);
			continue ;
		}
		else if (*token != '"')
		{
			token++;
			len++;
		}
		else if (*token == '"')
			token++;
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
