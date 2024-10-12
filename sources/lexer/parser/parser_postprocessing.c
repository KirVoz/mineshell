/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_postprocessing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 07:43:04 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 07:43:05 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	nullify_comment(t_cmd *cur, int i, int *flag)
{
	int			j;

	j = 0;
	while (cur->cmd[i][j])
	{
		if (cur->cmd[i][j] == '#')
			*flag = 1;
		if (*flag)
		{
			cur->cmd[i][j] = '\0';
			cur->whitespace[i] = 0;
		}
		j++;
	}
}

void	delete_comment(char *token, char *current_quote, int *comment_flag)
{
	int		i;

	i = 0;
	while (token[i] != '\0')
	{
		set_current_quote(current_quote, token[i], &token);
		if (token[i] == '#' && *current_quote != '\''
			&& *current_quote != '\"')
			*comment_flag = 1;
		if (*comment_flag)
			token[i] = '\0';
		i++;
	}
}

char	**rewrite_empty(t_minishell *minishell,
			char **tokens, char **new_tokens, int *new_ws)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
		{
			new_ws[j] = minishell->tmp->ws_tmp[i];
			new_tokens[j] = allocate_dup(tokens[i], "New_tokens[j]");
			j++;
		}
		if (minishell->tmp->ws_tmp[i] < 0)
			new_ws[j - 1] = minishell->tmp->ws_tmp[i];
		i++;
	}
	free(minishell->tmp->ws_tmp);
	minishell->tmp->ws_tmp = new_ws;
	new_tokens[j] = NULL;
	if (!new_tokens[0])
		new_tokens[0] = ft_strdup("");
	return (new_tokens);
}

char	**del_empty(t_minishell *minishell, char **tokens)
{
	int		i;
	int		j;
	char	**new_tokens;
	int		*new_ws;

	i = 0;
	j = 0;
	if (tokens[i][0] == '\0' && !tokens[i + 1])
		return (tokens);
	while (tokens[i])
	{
		if (tokens[i][0] == '\0' && i != 0)
			j++;
		i++;
	}
	new_tokens = allocate_array(array_len(tokens) - j, "New_tokens");
	new_ws = allocate_whitespaces(array_len(tokens) - j, "New_ws");
	new_tokens = rewrite_empty(minishell, tokens, new_tokens, new_ws);
	free_array(minishell->tmp->tokens);
	return (new_tokens);
}

void	delete_last_whitespace(t_cmd *cur)
{
	int		flag;
	int		i;
	int		j;

	flag = 0;
	j = -1;
	while (cur)
	{
		i = array_len(cur->cmd) - 1;
		if (cur->whitespace[i] > 0)
			cur->whitespace[i] = 0;
		while (cur->cmd[i][0] == '\0' && i > 0)
		{
			flag = 1;
			i--;
		}
		if (flag && cur->whitespace[i] == 1)
			cur->whitespace[i] = 0;
		while (++j <= i)
		{
			if (cur->whitespace[j] < 0)
				cur->whitespace[j] *= -1;
		}
		cur = cur->next;
	}
}
