/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese < kvoznese@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:31 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/29 01:37:38 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

char	*expand_question_mark(t_minishell *minishell, char *token,
			char *current_quote)
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
		set_current_quote_question(current_quote, *token);
		if (*token && *token == '$' && *(token + 1) && *(token + 1) == '?'
			&& *current_quote != '\'')
			write_exit_code(&result, exit_code, &i, &token);
		else if (*token)
			result[i++] = *(token++);
	}
	result[i] = '\0';
	free(exit_code);
	free(token_cp);
	return (result);
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

char	*expand(t_minishell *minishell, char *token, int *comment_flag)
{
	char	*expanded_token;
	char	current_quote;
	size_t	len;

	current_quote = 0;
	if (*token == '#' || *comment_flag == 1)
		delete_comment(token, &current_quote, comment_flag);
	if (ft_strnstr(token, "$?", ft_strlen(token)))
		token = expand_question_mark(minishell, token, &current_quote);
	// if 
	len = expanded_line_len(minishell, token, &current_quote);
	expanded_token = allocate_string(len, "Expanded_token in expand");
	expanded_token = substitute(minishell, token,
			expanded_token, &current_quote);
	free(token);
	return (expanded_token);
}

void	expander_main(t_minishell *minishell, char **tokens)
{
	int		comment_flag;
	int		i;

	i = 0;
	comment_flag = 0;
	while (tokens[i])
	{
		if ((!ft_strncmp(tokens[i], "\"\"", ft_strlen(tokens[i]))
				|| !ft_strncmp(tokens[i], "\'\'", ft_strlen(tokens[i]))))
			minishell->tmp->ws_tmp[i] = (minishell->tmp->ws_tmp[i]
					+ minishell->tmp->ws_tmp[i - 1]) * -1;
		tokens[i] = expand(minishell, tokens[i], &comment_flag);
		i++;
	}
	minishell->tmp->tokens = del_empty(minishell, tokens);
}
