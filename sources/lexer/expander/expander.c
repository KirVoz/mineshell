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

char	*expand_tilda(char *token, char *current_quote)
{
	char	*result;
	int		i;

	i = 0;
	result = allocate_string(ft_strlen(token) - 1 + 5, "Expand_question");
	result[0] = '\0';
	while (*token)
	{
		set_current_quote_question(current_quote, *token);
		if (*token && ((*token == '~' && !*(token + 1)) || ((*token == '~'
						&& *(token + 1) && *(token + 1) == '/'))
				|| ((*token == '~' && *(token + 1) && *(token + 1) == ':')))
			&& *current_quote != '\'')
		{
			ft_strlcat(&result[i], "$HOME", 5 + 1);
			i += 5;
		}
		else if (*token)
			result[i++] = *token;
		token++;
	}
	result[i] = '\0';
	return (result);
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
	if (ft_strncmp(token, "~\0", ft_strlen(token)) == 0 || (ft_strnstr(token,
				"~/", ft_strlen(token)) && check_before_tilde(token, 's'))
		|| (ft_strnstr(token, "~:", ft_strlen(token))
			&& check_before_tilde(token, 'd')))
		token = expand_tilda(token, &current_quote);
	len = expanded_line_len(minishell, token, &current_quote);
	expanded_token = allocate_string(len, "Expanded_token in expand");
	expanded_token = substitute(minishell, token, expanded_token,
			&current_quote);
	free(token);
	return (expanded_token);
}

void	expander_main(t_minishell *minishell, char **tokens)
{
	int	comment_flag;
	int	i;

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
