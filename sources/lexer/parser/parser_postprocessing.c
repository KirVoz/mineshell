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

char	**del_empty(char **tokens)
{
	int		i;
	int		j;
	char	**new_tokens;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '\0')
			j++;
		i++;
	}
	new_tokens = allocate_array(array_len(tokens) - j, "New_tokens");
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			new_tokens[j++] = ft_strdup(tokens[i]);
		i++;
	}
	new_tokens[j] = NULL;
	free_array(tokens);
	return (new_tokens);
}

void	delete_last_whitespace(t_cmd *cur)
{
	int		flag;
	int		i;

	flag = 0;
	while (cur)
	{
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
		cur = cur->next;
	}
}
