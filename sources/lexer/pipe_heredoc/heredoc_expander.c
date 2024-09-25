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

size_t	exit_len_hc(char *token, char *exit_code)
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
		else
			len++;
		token++;
	}
	return (len);
}

char	*expand_question_mark_heredoc(t_minishell *minishell, char *token)
{
	char	*result;
	char	*token_cp;
	char	*exit_code;
	int		i;

	i = 0;
	token_cp = token;
	exit_code = ft_itoa(minishell->exit_code);
	result = allocate_string(exit_len_hc(token, exit_code), "Expand_question");
	while (*token)
	{
		if (*token == '$' && *(token + 1) && *(token + 1) == '?')
		{
			write_exit_code(&result, exit_code, &i);
			token += 2;
		}
		else
			result[i++] = *(token++);
	}
	result[i] = '\0';
	free(exit_code);
	free(token_cp);
	return (result);
}

char	*substitute_heredoc_env(t_minishell *minishell,
		char *token, char *result)
{
	char	*token_cp;
	int		i;

	token_cp = token;
	i = 0;
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
	return (result);
}

void	heredoc_expander(t_minishell *minishell, char **tokens)
{
	size_t	len;
	int		i;
	char	*tmp_token;

	i = 0;
	while (tokens[i])
	{
		tmp_token = tokens[i];
		if (ft_strnstr(tokens[i], "$?", ft_strlen(tokens[i])))
			tokens[i] = expand_question_mark_heredoc(minishell, tokens[i]);
		else if (ft_strchr(tokens[i], '$') && ft_strlen(tokens[i]) > 1)
		{
			len = count_to_dollar(&tokens[i])
				+ env_value_len(minishell, &tokens[i]) + ft_strlen(tokens[i]);
			tokens[i] = allocate_string(len, "Heredoc_expander");
			tokens[i] = substitute_heredoc_env(minishell, tmp_token, tokens[i]);
			free(tmp_token);
		}
		i++;
	}
	tmp_token = NULL;
}
