/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:13:14 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:41:08 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_arg(char *new_var)
{
	int	i;

	i = 0;
	if (new_var[i] == '@' || new_var[i] == '*' || new_var[i] == '^'
		|| new_var[i] == '?' || new_var[i] == '-' || new_var[i] == '$'
		|| new_var[i] == '!' || new_var[i] == '~' || new_var[i] == '.'
		|| new_var[i] == '{' || new_var[i] == '}')
		return (2);
	if (new_var[i] >= '0' && new_var[i] <= '9' && new_var[i] != '=')
		return (1);
	while (new_var[i])
	{
		if (new_var[i] == '@' || new_var[i] == '*' || new_var[i] == '^'
			|| new_var[i] == '?' || new_var[i] == '-' || new_var[i] == '$'
			|| new_var[i] == '!' || new_var[i] == '~' || new_var[i] == '.'
			|| new_var[i] == '{' || new_var[i] == '}')
			return (1);
		if (new_var[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

static int	find_env_index(char **env_array, const char *var_name)
{
	size_t	var_name_len;
	int		i;

	i = -1;
	var_name_len = ft_strlen(var_name);
	while (env_array[++i])
	{
		if (ft_strncmp(env_array[i], var_name, var_name_len) == 0
			&& env_array[i][var_name_len] == '=')
			return (i);
	}
	return (-1);
}

static void	remove_env_var(char **env_array, int index)
{
	int	j;

	free(env_array[index]);
	j = index;
	while (env_array[j + 1] != NULL)
	{
		env_array[j] = env_array[j + 1];
		j++;
	}
	env_array[j] = env_array[j + 1];
}

void	execute_unset(t_minishell *minishell, int fd, t_cmd *cur)
{
	int	i;
	int	index;

	(void)fd;
	if (cur->cmd[1] == NULL)
		return ;
	i = 1;
	while (cur->cmd[i] != NULL)
	{
		if (valid_arg(cur->cmd[i]) == 1)
		{
			not_valid(minishell, cur->cmd[i], 1, 0);
			return ;
		}
		else if (valid_arg(cur->cmd[i]) == 2)
		{
			not_valid(minishell, cur->cmd[i], 2, 0);
			return ;
		}
		index = find_env_index(minishell->env, cur->cmd[i]);
		if (index != -1)
			remove_env_var(minishell->env, index);
		i++;
	}
	minishell->exit_code = 0;
}
