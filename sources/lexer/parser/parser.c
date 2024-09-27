/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:25:28 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:25:30 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	process_token(t_minishell **minishell, t_cmd *current,
			char *token, int *i)
{
	if (is_redirection(token))
	{
		handle_redirections(current, token, (*minishell)->tmp->tokens[*i + 1]);
		if (ft_strncmp(token, "<<", 2) == 0)
			current->heredoc = (*minishell)->tmp->heredoc_tmp
			[(*minishell)->tmp->current_heredoc++];
		*i += 2;
	}
	else
	{
		add_command(current, token);
		(*i)++;
	}
}

void	parser_main(t_minishell **minishell, char ***tokens)
{
	t_cmd	*current;
	t_cmd	*cmd_list;
	int		cmd_count;
	int		i;

	current = NULL;
	cmd_list = NULL;
	cmd_count = array_len(*tokens);
	i = 0;
	while ((*tokens)[i])
	{
		process_node(&current, &cmd_list, (*tokens)[i], cmd_count);
		if (is_pipe((*tokens)[i]))
		{
			i++;
			continue ;
		}
		process_token(minishell, current, (*tokens)[i], &i);
		if (!current->cmd)
			current->cmd = array_init();
	}
	(*minishell)->cmd = cmd_list;
}
