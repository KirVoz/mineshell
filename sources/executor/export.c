/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:08 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 19:44:52 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	update(t_minishell *minishell, const char *new_var, int env_count)
{
	minishell->env = ft_realloc(minishell->env, sizeof(char *) * (env_count),
		sizeof(char *) * (env_count + 2));
	if (minishell->env == NULL)
		exit_fail("Failed to allocate memory for envp_var");
	minishell->env[env_count] = ft_strdup(new_var);
	if (minishell->env[env_count] == NULL)
		exit_fail("Failed to allocate memory for new_var");
	minishell->env[env_count + 1] = NULL;
}

static void	add_or_update_env_var(t_minishell *minishell, const char *new_var)
{
	size_t	i;
	char	*existing_var;
	size_t	env_count;
	size_t	var_name_len;

	env_count = array_len(minishell->env);
	var_name_len = ft_strchr(new_var, '=') - new_var;
	i = -1;
	while (++i < env_count)
	{
		existing_var = minishell->env[i];
		if (ft_strncmp(existing_var, new_var, var_name_len) == 0
			&& (existing_var[var_name_len] == '='
				|| existing_var[var_name_len] == '\0'))
		{
			free(minishell->env[i]);
			minishell->env[i] = ft_strdup(new_var);
			if (minishell->env[i] == NULL)
				exit_fail("Failed to allocate memory for envp_var element");
			return ;
		}
	}
	update(minishell, new_var, env_count);
	minishell->exit_code = 0;
}

void	declare_env_var(t_minishell *minishell, int fd)
{
	char	*declare;
	size_t	env_count;
	size_t	i;

	env_count = array_len(minishell->env);
	i = -1;
	while (++i < env_count)
	{
		declare = construct_declare(minishell->env[i]);
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(declare, fd);
		ft_putstr_fd("\n", 1);
		free(declare);
	}
}

static void	handle_invalid_identifier(t_minishell *minishell, char *new_var,
	int bash_err)
{
	if (bash_err)
		not_valid(minishell, new_var, 2);
	else
	{
		not_valid(minishell, new_var, 1);
		if (minishell->tmp->is_child != 0)
			exit(minishell->exit_code);
	}
}

void	execute_export(t_minishell *minishell, int fd, t_cmd *cur)
{
	char	*new_var;
	int		i;

	i = 1;
	if (cur->cmd[i] && ft_check_valid_simbol(cur->cmd[i]) == 1)
	{
		handle_invalid_identifier(minishell, cur->cmd[i], 1);
		return ;
	}
	if (validation_check(minishell, cur, fd, &i) == 1)
	{
		new_var = cur->cmd[i];
		if (ft_check_valid_identifier(new_var) == 3)
		{
			minishell->exit_code = 0;
			return ;
		}
		else if (ft_check_valid_identifier(new_var) == 1)
			return (handle_invalid_identifier(minishell, new_var, 0));
		else if (ft_check_valid_identifier(new_var) != 3)
			add_or_update_env_var(minishell, new_var);
	}
	return ;
}
