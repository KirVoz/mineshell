/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:27 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:39:10 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

volatile sig_atomic_t	g_child = 0;

static void	execute_child(t_minishell *minishell, t_cmd *current,
		int i, int num_cmd)
{
	redirects(minishell, current, i, num_cmd);
	close_pipes(minishell->pipes, num_cmd);
	if (is_builtin(current->cmd[0]))
	{
		execute_command(minishell, STDOUT_FILENO, current);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (!path_present(minishell))
			return (no_path_file(minishell, current->cmd[0]));
		if (file_dir_check(current->cmd[0]))
			return (handle_file_dir(minishell, current->cmd));
		if (!get_path(minishell, current->cmd[0])
			|| !ft_strncmp(current->cmd[0], ".", ft_strlen(current->cmd[0]))
			|| !ft_strncmp(current->cmd[0], "..", ft_strlen(current->cmd[0])))
		{
			not_found(minishell, current->cmd[0]);
			exit(minishell->exit_code);
		}
		ft_free_exe_free(minishell, current);
		exit(minishell->exit_code);
	}
}

static pid_t	*fork_processes(t_minishell *minishell, int num_cmd)
{
	t_cmd	*cur;
	pid_t	*pids;
	int		i;

	i = -1;
	cur = minishell->cmd;
	pids = malloc(sizeof(pid_t) * num_cmd);
	while (++i < num_cmd)
	{
		pids[i] = fork();
		g_child = 1;
		if (pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
			execute_child(minishell, cur, i, num_cmd);
		cur = cur->next;
	}
	return (pids);
}

static void	wait_for_processes(pid_t *pids, int num_cmd, t_minishell *minishell)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = 0;
	i = 0;
	while (i < num_cmd)
	{
		waitpid(pids[i], &status, 0);
		if (!g_child && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	minishell->exit_code = exit_code;
}

static void	execute_commands(t_minishell *minishell)
{
	int		num_cmd;
	pid_t	*pids;

	num_cmd = count_commands(minishell->cmd);
	pids = NULL;
	if (num_cmd == 1 && solo_builtin(minishell->cmd->cmd[0]))
	{
		minishell->tmp->is_child = 0;
		execute_command(minishell, STDOUT_FILENO, minishell->cmd);
	}
	else
	{
		if (num_cmd > 1)
			minishell->pipes = setup_pipes(num_cmd);
		pids = fork_processes(minishell, num_cmd);
		if (num_cmd > 1)
		{
			close_pipes(minishell->pipes, num_cmd);
			free_pipes(minishell->pipes, num_cmd);
		}
		wait_for_processes(pids, num_cmd, minishell);
		g_child = 0;
		free(pids);
	}
}

void	execute(t_minishell *minishell)
{
	int		i;
	t_cmd	*tmp;

	tmp = minishell->cmd;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (i == 1)
		update_underscore_variable(minishell);
	if (i > 1 && !ft_strncmp(minishell->cmd->cmd[0], "env", 3))
		update_underscore_variable(minishell);
	execute_commands(minishell);
	free_minishell(minishell);
}
