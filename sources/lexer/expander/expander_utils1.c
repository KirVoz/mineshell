/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:54 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/30 16:51:01 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	expand_to_env(t_minishell *minishell, char **cur_ptr, char cur_quote)
{
	char	*env_value;

	env_value = get_env_value(minishell, cur_ptr);
	if (env_value || cur_quote == '"')
	{
		free(env_value);
		return (1);
	}
	return (0);
}

void	write_exit_code(char **result, char *exit_code, int *i, char **token)
{
	while (*exit_code)
	{
		(*result)[*i] = *exit_code;
		(*i)++;
		exit_code++;
	}
	*token += 2;
}

void	set_current_quote(char *current_quote, char quote, char **token)
{
	static int	quote_counter;

	if (ft_strchr(QUOTES, quote))
	{
		if (!*current_quote)
		{
			*current_quote = quote;
			quote_counter++;
		}
		else if (*current_quote == quote)
			quote_counter++;
		if (quote_counter % 2 == 0)
		{
			quote_counter = 0;
			*current_quote = 0;
			(*token)++;
		}
	}
}

void	set_current_quote_question(char *current_quote, char quote)
{
	static int	quote_counter;

	if (ft_strchr(QUOTES, quote))
	{
		if (!*current_quote)
		{
			*current_quote = quote;
			quote_counter++;
		}
		else if (*current_quote == quote)
			quote_counter++;
		if (quote_counter % 2 == 0)
		{
			quote_counter = 0;
			*current_quote = 0;
		}
	}
}

char	*substitute(t_minishell *minishell, char *token,
		char *exp_token, char *current_quote)
{
	int		j;
	int		n;
	char	*env_value;

	j = 0;
	n = 0;
	while (*token)
	{
		set_current_quote(current_quote, *token, &token);
		if (*token == '$' && *(token + 1) && (ft_isalnum(*(token + 1))
				|| *(token + 1) == '_') && *current_quote != '\'')
		{
			env_value = get_env_value(minishell, &token);
			while (env_value[n])
				exp_token[j++] = env_value[n++];
			free(env_value);
			n = 0;
		}
		else if (*token != *current_quote)
			exp_token[j++] = *(token++);
		else if (*token && *token == *current_quote)
			token++;
	}
	exp_token[j] = '\0';
	return (exp_token);
}
