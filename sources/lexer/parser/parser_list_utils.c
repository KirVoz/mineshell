/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:25:35 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:25:37 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	process_node(t_cmd **current, t_cmd **cmd_list,
		char *token, int cmd_count)
{
	t_cmd	*command_node;
	t_cmd	*last;

	if (!*current || is_pipe(token))
	{
		command_node = init_cmd_node(cmd_count);
		if (!*cmd_list)
			*cmd_list = command_node;
		else
		{
			last = *cmd_list;
			while (last->next)
				last = last->next;
			last->next = command_node;
			command_node->inpipe = 1;
			last->outpipe = 1;
		}
		*current = command_node;
	}
}

void	add_command(t_minishell **minishell, t_cmd *current,
		char *token, int *i)
{
	int		command_len;
	char	**command;

	if (!current)
		exit_fail("Empty current node in add_command");
	command_len = 0;
	if (current->cmd)
	{
		while (current->cmd[command_len])
			command_len++;
	}
	command = (char **)ft_realloc(current->cmd, command_len * sizeof(char *),
			(command_len + 2) * sizeof(char *));
	if (!command)
		exit_fail("Failed to allocate memory for command");
	current->cmd = command;
	current->cmd[command_len] = ft_strdup(token);
	if ((*minishell)->tmp->ws_tmp[*i] == 1)
		current->whitespace[command_len] = 1;
	if (!current->cmd[command_len])
		exit_fail("Failed to duplicate token in add_command");
	current->cmd[command_len + 1] = NULL;
}
