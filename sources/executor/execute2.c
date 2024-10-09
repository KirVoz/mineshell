/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:23:36 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:34:02 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	solo_builtin(char *cmd)
{
	int		len;
	char	*cmd_lower;

	len = ft_strlen(cmd);
	cmd_lower = str_to_lower(cmd);
	if (ft_strncmp(cmd_lower, "cd", len) == 0 || ft_strncmp(cmd_lower, "export",
			len) == 0 || ft_strncmp(cmd_lower, "unset", len) == 0
		|| ft_strncmp(cmd_lower, "env", len) == 0 || ft_strncmp(cmd_lower,
			"exit", len) == 0)
	{
		free(cmd_lower);
		return (1);
	}
	free(cmd_lower);
	return (0);
}

int	is_builtin(char *cmd)
{
	int		len;
	char	*cmd_lower;

	len = ft_strlen(cmd);
	cmd_lower = str_to_lower(cmd);
	if (ft_strncmp(cmd_lower, "echo", len) == 0 || ft_strncmp(cmd_lower, "cd",
			len) == 0 || ft_strncmp(cmd_lower, "pwd", len) == 0
		|| ft_strncmp(cmd_lower, "export", len) == 0 || ft_strncmp(cmd_lower,
			"unset", len) == 0 || ft_strncmp(cmd_lower, "env", len) == 0
		|| ft_strncmp(cmd_lower, "exit", len) == 0)
	{
		free(cmd_lower);
		return (1);
	}
	free(cmd_lower);
	return (0);
}

void	free_pipes(int **pipes, int num_cmd)
{
	int	i;

	i = 0;
	while (i < num_cmd - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	write_heredoc_to_fd(t_cmd *cmd, int fd)
{
	int	j;

	j = 0;
	while (cmd->heredoc[j] != NULL)
	{
		write(fd, cmd->heredoc[j], ft_strlen(cmd->heredoc[j]));
		write(fd, "\n", 1);
		j++;
	}
}

void	heredoc_fd(t_cmd *cmd)
{
	int	heredoc_fd[2];

	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	write_heredoc_to_fd((cmd), heredoc_fd[1]);
	close(heredoc_fd[1]);
	if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 file");
		exit(EXIT_FAILURE);
	}
	close(heredoc_fd[0]);
}
