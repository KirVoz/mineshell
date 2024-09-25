/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:31 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:24:33 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	processing_quoted_line(t_minishell *minishell, char **token,
		char *result, char *current_quote)
{
	int		in_quote;

	if (*current_quote == 0)
		in_quote = 0;
	else
		in_quote = 1;
	if ((**token == '\'' || **token == '\"') && !in_quote)
		*current_quote = set_quote(**token, &in_quote);
	else if (**token == *current_quote && in_quote)
		in_quote = 0;
	else if (**token == '$' && *current_quote == '"'
		&& !(*(*token + 1) == '"' || *(*token + 1) == '\''))
	{
		substitute_env(minishell, token, &result, &minishell->tmp->i);
		(*token)--;
		return ;
	}
	else if (**token != *current_quote || in_quote)
	{
		result[minishell->tmp->i] = **token;
		minishell->tmp->i++;
	}
}

char	*expand_quoted_line(t_minishell *minishell, char *token, size_t len)
{
	char	*result;
	char	*token_cp;
	char	current_quote;

	token_cp = token;
	current_quote = 0;
	result = allocate_string(len, "Result in expand_line");
	while (*token_cp)
	{
		processing_quoted_line(minishell, &token_cp,
			result, &current_quote);
		token_cp++;
	}
	result[minishell->tmp->i] = '\0';
	minishell->tmp->i = 0;
	free(token);
	return (result);
}

char	*expand_dollar_line(t_minishell *minishell, char *token, size_t len)
{
	char	*token_cp;
	char	*result;
	int		i;

	token_cp = token;
	i = 0;
	result = allocate_string(len, "Result in expand_line");
	while (*token_cp)
	{
		if (*token_cp == '$' && *(token_cp + 1))
		{
			substitute_env(minishell, &token_cp, &result, &i);
			continue ;
		}
		else
		{
			result[i] = *token_cp;
			i++;
		}
		token_cp++;
	}
	result[i] = '\0';
	free(token);
	return (result);
}

char	*expand_question_mark(t_minishell *minishell, char *token)
{
	char	*result;
	char	*token_cp;
	char	*exit_code;
	int		i;

	i = 0;
	token_cp = token;
	exit_code = ft_itoa(minishell->exit_code);
	result = allocate_string(exit_len(token, exit_code), "Expand_question");
	while (*token)
	{
		if (*token == '$' && *(token + 1) && *(token + 1) == '?')
		{
			write_exit_code(&result, exit_code, &i);
			token += 2;
		}
		else if (*token == '"')
			token++;
		else
			result[i++] = *(token++);
	}
	result[i] = '\0';
	free(exit_code);
	free(token_cp);
	return (result);
}

void	expander_main(t_minishell *minishell, char **tokens)
{
	char	*token_cp;
	size_t	new_line_len;

	new_line_len = 0;
	while (*tokens)
	{
		token_cp = *tokens;
		if (ft_strnstr(*tokens, "$?", ft_strlen(*tokens))
			&& !ft_strchr(*tokens, '\''))
			*tokens = expand_question_mark(minishell, *tokens);
		else if (ft_strchr(*tokens, '"') || ft_strchr(*tokens, '\''))
		{
			new_line_len = expanded_line_len(minishell, token_cp);
			*tokens = expand_quoted_line(minishell, *tokens, new_line_len);
		}
		else if (ft_strchr(*tokens, '$') && ft_strlen(*tokens) > 1)
		{
			if (**tokens != '$')
				new_line_len += count_to_dollar(&token_cp);
			new_line_len += env_value_len(minishell, &token_cp);
			*tokens = expand_dollar_line(minishell, *tokens, new_line_len);
		}
		tokens++;
	}
	token_cp = NULL;
}
