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

void	proccess_whitespace(t_minishell *minishell,
		t_cmd *current, char **token, int i)
{
	int		len;

	len = 0;
	while ((*token)[len])
		len++;
	if (len != 0 && (*token)[len - 1] == ' ')
	{
		current->whitespace[i] = 1;
		*token = (char *)ft_realloc(*token, (len + 1) * sizeof(char),
				len * sizeof(char));
		if (!*token)
			exit_fail("token in proccess_whitespace");
		(*token)[len - 1] = '\0';
		if (minishell->tmp->tokens[i + 1] && (*(minishell->tmp->tokens
					[i + 1]) == '<' || *(minishell->tmp->tokens[i + 1]) == '>'
				|| *(minishell->tmp->tokens[i + 1]) == '|'))
			current->whitespace[i] = 0;
	}
	else
		current->whitespace[i] = 0;
}

void	add_command(t_minishell *minishell, t_cmd *current, char *token, int i)
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
	proccess_whitespace(minishell, current, &current->cmd[command_len], i);
	if (!current->cmd[command_len])
		exit_fail("Failed to duplicate token in add_command");
	current->cmd[command_len + 1] = NULL;
}
