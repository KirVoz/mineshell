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

char	*substitute(t_minishell *minishell, char *token, char *exp_token)
{
	int		j;
	int		n;
	char	*env_value;

	j = 0;
	n = 0;
	while (*token)
	{
		if (*token == '$' && *(token + 1) && *(token + 1) != '$')
		{
			env_value = get_env_value(minishell, &token);
			if (*env_value == '\0' && *token == ' ')
				token++;
			while (env_value[n])
				exp_token[j++] = env_value[n++];
			free(env_value);
			n = 0;
		}
		else if (*token != '"')
			exp_token[j++] = *(token++);
		else if (*token == '"')
			token++;
	}
	exp_token[j] = '\0';
	return (exp_token);
}

char	*expand(t_minishell *minishell, char *token, int i)
{
	char	*expanded_token;
	size_t	len;

	(void)i;
	if (ft_strnstr(token, "$?", ft_strlen(token)))
		return (expand_question_mark(minishell, token));
	len = expanded_line_len(minishell, token);
	expanded_token = allocate_string(len, "Expanded_token in expand");
	expanded_token = substitute(minishell, token, expanded_token);
	free(token);
	return (expanded_token);
}

void	expander_main(t_minishell *minishell, char **tokens)
{
	int			i;
	t_cmd		*cur;

	i = 0;
	cur = minishell->cmd;
	(void)tokens;
	while (cur)
	{
		while (cur->cmd[i])
		{
			cur->cmd[i] = expand(minishell, cur->cmd[i], i);
			i++;
		}
		i = 0;
		cur = cur->next;
	}
}
