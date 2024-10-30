/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:38 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:14:40 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(t_minishell *minishell, int fd, t_cmd *cur)
{
	int	i;

	(void)fd;
	(void)cur;
	i = 1;
	while (cur->cmd[i] != NULL)
	{
		arg_count_error(minishell, "env", 0);
		i++;
		return ;
	}
	while (minishell->env[i] != NULL)
	{
		ft_putstr_fd(minishell->env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	minishell->exit_code = 0;
}
