/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:54 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:24:55 by aaleksee         ###   ########.fr       */
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
		*token += 2;
	}
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

void	delete_last_whitespace(t_cmd *cur)
{
	int		flag;
	int		i;

	flag = 0;
	i = array_len(cur->cmd) - 1;
	if (cur->whitespace[i] == 1)
		cur->whitespace[i] = 0;
	while (cur->cmd[i][0] == '\0' && i > 0)
	{
		flag = 1;
		i--;
	}
	if (flag && cur->whitespace[i] == 1)
		cur->whitespace[i] = 0;
}

void	delete_comment(t_cmd *cur)
{
	int		i;
	int		j;
	int 	flag;

	i = 0;
	flag = 0;
	while (cur->cmd[i])
	{
		j = 0;
		while (cur->cmd[i][j])
		{
			if (cur->cmd[i][j] == '#' && i > 0 && cur->whitespace[i - 1])
				flag = 1;
			if (flag)
			{
				cur->cmd[i][j] = '\0';
				cur->whitespace[i] = 0;
			}
			j++;
		}
		i++;
	}
}
