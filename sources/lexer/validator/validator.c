/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:25:10 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:25:11 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	hanging_tokens(char **tokens)
{
	size_t	token_len;

	while (*tokens)
	{
		token_len = ft_strlen(*tokens);
		if ((ft_strncmp(*tokens, "<", token_len) == 0
				|| ft_strncmp(*tokens, ">", token_len) == 0
				|| ft_strncmp(*tokens, "<<", token_len) == 0
				|| ft_strncmp(*tokens, ">>", token_len) == 0
				|| ft_strncmp(*tokens, "|", token_len) == 0) && !*(tokens + 1)
			&& token_len != 0)
			return (1);
		tokens++;
	}
	return (0);
}

int	is_valid_token(char *token)
{
	char	**valid_toks;
	int		i;

	i = 0;
	valid_toks = get_valid_tokens();
	while (valid_toks[i])
	{
		if (ft_strncmp(token, valid_toks[i], ft_strlen(valid_toks[i])) == 0)
		{
			free(valid_toks);
			return (1);
		}
		i++;
	}
	free(valid_toks);
	return (0);
}

int	pipe_redirections_mistake(t_minishell *minishell, char **tokens)
{
	if (**tokens == '|')
		return (syntax_error(minishell, "|"));
	while (*tokens)
	{
		if (is_valid_token(*tokens) && *(tokens + 1)
			&& **(tokens + 1) == '|')
			return (syntax_error(minishell, *(tokens + 1)) + 1);
		tokens++;
	}
	return (0);
}

int	validator_main(t_minishell *minishell, char ***tokens)
{
	if (pipe_redirections_mistake(minishell, *tokens))
		return (0);
	if (hanging_tokens(*tokens))
		return (syntax_error(minishell, "newline"));
	return (1);
}
