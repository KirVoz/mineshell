/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:33:03 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 19:43:56 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	append_to_environment(t_minishell *minishell, char *new_value)
{
	int		env_len;
	char	**new_env;
	int		j;

	env_len = 0;
	while (minishell->env[env_len] != NULL)
		env_len++;
	new_env = (char **)malloc(sizeof(char *) * (env_len + 3));
	if (!new_env)
		exit_fail("Failed to allocate memory for new environment variable");
	j = 0;
	while (j < env_len)
	{
		new_env[j] = minishell->env[j];
		j++;
	}
	new_env[env_len] = ft_strdup(new_value);
	new_env[env_len + 1] = NULL;
	free(minishell->env);
	minishell->env = NULL;
	minishell->env = new_env;
}

static void	shift_environment(char **env, int index)
{
	while (env[index] != NULL)
	{
		env[index] = env[index + 1];
		index++;
	}
	env[index] = NULL;
}

static void	update_environment(t_minishell *minishell, char *new_value)
{
	int	index;

	index = find_string_in_array(minishell->env, "_=", 2);
	if (index != -1)
	{
		free(minishell->env[index]);
		shift_environment(minishell->env, index);
	}
	append_to_environment(minishell, new_value);
}

static char	*get_last_command(t_minishell *minishell)
{
	t_cmd	*tmp;
	int		i;
	char	*full_path;

	tmp = minishell->cmd;
	full_path = NULL;
	i = -1;
	while (tmp->cmd[++i])
	{
		if (tmp->cmd[i + 1] == NULL)
		{
			if (i == 0)
			{
				full_path = get_path(minishell, tmp->cmd[i]);
				if (full_path)
					return (full_path);
				else
					return (tmp->cmd[i]);
			}
			else
				return (tmp->cmd[i]);
		}
	}
	return (NULL);
}

void	update_underscore_variable(t_minishell *minishell)
{
	char	*last_cmd;
	char	*new_value;

	last_cmd = get_last_command(minishell);
	if (last_cmd)
	{
		new_value = ft_strjoin("_=", last_cmd);
		if (!new_value)
			exit_fail("Failed to allocate memory for _= variable");
		update_environment(minishell, new_value);
		free(new_value);
	}
}
