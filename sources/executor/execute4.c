/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:31:40 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:32:34 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	count_commands(t_cmd *cmd)
{
	int	num_cmd;

	num_cmd = 0;
	while (cmd)
	{
		num_cmd++;
		cmd = cmd->next;
	}
	return (num_cmd);
}

int	**setup_pipes(int num_cmd)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = malloc(sizeof(int *) * (num_cmd - 1));
	while (++i < num_cmd - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (pipes);
}
