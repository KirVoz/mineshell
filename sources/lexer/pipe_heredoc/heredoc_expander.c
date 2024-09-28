/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:05:07 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 13:05:08 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

char	*expand_question_mark_hd(t_minishell *minishell, char *token)
{
	char	*result;
	char	*token_cp;
	char	*exit_code;
	int		i;

	i = 0;
	token_cp = token;
	exit_code = ft_itoa(minishell->exit_code);
	result = allocate_string(exit_len_hd(token, exit_code), "Expand_question");
	while (*token)
	{
		if (*token == '$' && *(token + 1) && *(token + 1) == '?')
			write_exit_code(&result, exit_code, &i, &token);
		else
			result[i++] = *(token++);
	}
	result[i] = '\0';
	free(exit_code);
	free(token_cp);
	return (result);
}

char	*substitute_hd(t_minishell *minishell, char *token, char *exp_token)
{
	int		j;
	int		n;
	char	*env_value;

	j = 0;
	n = 0;
	while (*token)
	{
		if (*token == '$' && *(token + 1) && ft_isalnum(*(token + 1)))
		{
			env_value = get_env_value(minishell, &token);
			while (env_value[n])
				exp_token[j++] = env_value[n++];
			free(env_value);
			n = 0;
		}
		else
			exp_token[j++] = *(token++);
	}
	exp_token[j] = '\0';
	return (exp_token);
}

size_t	expanded_line_len_hd(t_minishell *minishell, char *token)
{
	size_t	len;
	char	*env_value;

	len = 0;
	while (*token)
	{
		if (*token == '$' && *(token + 1) && ft_isalnum(*(token + 1)))
		{
			env_value = get_env_value(minishell, &token);
			len += ft_strlen(env_value);
			free(env_value);
			continue ;
		}
		else
		{
			token++;
			len++;
		}
	}
	return (len);
}

char	*expand_hd(t_minishell *minishell, char *token)
{
	char	*expanded_token;
	size_t	len;

	if (ft_strnstr(token, "$?", ft_strlen(token)))
		token = expand_question_mark_hd(minishell, token);
	len = expanded_line_len_hd(minishell, token);
	expanded_token = allocate_string(len, "Expanded_token in expand");
	expanded_token = substitute_hd(minishell, token, expanded_token);
	free(token);
	return (expanded_token);
}

void	heredoc_expander(t_minishell *minishell, char **tokens)
{
	while (*tokens)
	{
		*tokens = expand_hd(minishell, *tokens);
		tokens++;
	}
}
