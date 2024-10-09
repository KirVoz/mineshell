/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:27:06 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:29:55 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	open_file(t_minishell *minishell, const char *filename,
		int perm_or_no_file)
{
	if (access(filename, R_OK) == -1 || access(filename, W_OK) == -1)
	{
		if (perm_or_no_file == 1)
			permission_denied(minishell, (char *)filename, 1);
		else
			no_file(minishell, (char *)filename);
		exit(minishell->exit_code);
	}
	else
		return ;
}

void	close_pipes(int **pipes, int num_cmd)
{
	int	j;

	j = -1;
	while (++j < num_cmd - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
}

int	path_present(t_minishell *minishell)
{
	int	i;

	i = -1;
	while (minishell->env[++i] != NULL)
	{
		if (ft_strncmp(minishell->env[i], "PATH=", 5) == 0)
			break ;
	}
	if (minishell->env[i])
		return (1);
	return (0);
}

int	file_dir_check(char *cmd)
{
	while (ft_isspace(*cmd))
		cmd++;
	if ((*cmd == '.' || *cmd == '/' || (*cmd == '.' && *(cmd + 1) == '/')
			|| (*cmd == '.' && *(cmd + 1) == '.' && *(cmd + 2) == '/'))
		&& ft_strncmp(cmd, "./minishell", ft_strlen(cmd)) != 0)
		return (1);
	return (0);
}

void	handle_file_dir(t_minishell *minishell, char **cmd)
{
	struct stat	stat_buf;

	stat(*cmd, &stat_buf);
	if (access(*cmd, F_OK) == -1)
	{
		no_path_file(minishell, *cmd);
		exit(minishell->exit_code);
	}
	else if (access(*cmd, F_OK) == 0 && S_ISDIR(stat_buf.st_mode))
	{
		is_a_directory(minishell, *cmd, 'e');
		exit(minishell->exit_code);
	}
	else if (access(*cmd, X_OK) == -1)
	{
		permission_denied(minishell, *cmd, 0);
		exit(minishell->exit_code);
	}
}
