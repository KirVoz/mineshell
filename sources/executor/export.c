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

static int	check_symbols_before_equal(t_minishell *minishell,
	char *cmd, int *status)
{
	int	j;

	j = 0;
	while (cmd[j] != '=')
	{
		if (ft_check_valid_symbol(cmd, j, 1) == 1)
		{
			not_valid(minishell, cmd, 1);
			*status = 1;
			return (0);
		}
		else if (j == 0 && ft_check_valid_symbol(cmd, j, 0) == 1)
		{
			not_valid(minishell, cmd, 2);
			*status = 1;
			return (0);
		}
		else if (ft_check_valid_symbol(cmd, j, 1) == 2)
		{
			concatinate_env_var(minishell, cmd);
			return (0);
		}
		j++;
	}
	return (j);
}

static void	handle_argument_with_equal(t_minishell *minishell,
	char *cmd, int *status)
{
	int	j;

	j = 0;
	if (cmd[j] == '=' || cmd[j] == '+')
	{
		not_valid(minishell, cmd, 2);
		*status = 1;
		return ;
	}
	j = check_symbols_before_equal(minishell, cmd, status);
	if (cmd[j] == '=' && *status == 0)
		add_or_update_env_var(minishell, cmd);
}

static void	handle_argument_without_equal(t_minishell *minishell,
	char *cmd, int *status)
{
	int	j;

	j = 0;
	while (cmd[j] != '\0')
	{
		if (ft_check_valid_symbol(cmd, j, 1) == 1)
		{
			not_valid(minishell, cmd, 1);
			*status = 1;
			return ;
		}
		else if (j == 0 && ft_check_valid_symbol(cmd, j, 0) == 1)
		{
			not_valid(minishell, cmd, 2);
			*status = 1;
			return ;
		}
		j++;
	}
	if (*status == 0 && ft_strchr(cmd, '='))
		add_or_update_env_var(minishell, cmd);
}

void	execute_export(t_minishell *minishell, int fd, t_cmd *cur)
{
	int	i;
	int	status;

	if (cur->cmd[1] == NULL || cur->cmd[1][0] == '\0')
	{
		declare_env_var(minishell, fd);
		return ;
	}
	i = 1;
	status = 0;
	while (cur->cmd[i] != NULL)
	{
		if (ft_strchr(cur->cmd[i], '='))
			handle_argument_with_equal(minishell, cur->cmd[i],
				&status);
		else
			handle_argument_without_equal(minishell, cur->cmd[i],
				&status);
		i++;
	}
	if (status == 1)
		minishell->exit_code = 1;
}
