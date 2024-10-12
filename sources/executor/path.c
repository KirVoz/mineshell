/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:13:50 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:13:52 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	**get_paths(t_minishell *minishell)
{
	int	i;

	i = -1;
	while (minishell->env[++i] != NULL)
	{
		if (ft_strncmp(minishell->env[i], "PATH=", 5) == 0)
			break ;
	}
	if (minishell->env[i])
		return (ft_split(minishell->env[i] + 5, ':'));
	return (NULL);
}

static char	*find_executable(char **paths, char *cmd)
{
	char	*part_path;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static bool	is_explicit_path(const char *cmd)
{
	return (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '.'
			&& cmd[1] == '.' && cmd[2] == '/'));
}

char	*get_path(t_minishell *minishell, char *cmd)
{
	char	**paths;

	if (*cmd == '\0')
		return (NULL);
	if (is_explicit_path(cmd))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	paths = get_paths(minishell);
	if (paths == NULL)
		return (NULL);
	minishell->path = find_executable(paths, cmd);
	ft_free_split(paths);
	return (minishell->path);
}
