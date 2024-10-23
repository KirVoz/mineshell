/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:21:17 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:22:00 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_str(char *str)
{
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	str += 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

static int	is_n_sequence(char *str)
{
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

static int	check_newline(char **cmd, int *whitespace, int *i)
{
	int	current;
	int	newline;

	current = *i;
	newline = 1;
	if (!cmd[current] || !is_n_str(cmd[current]))
		return (1);
	current++;
	while (cmd[current] && (is_n_str(cmd[current]) || (!whitespace[current - 1]
				&& is_n_sequence(cmd[current]))))
		current++;
	if (current > *i)
	{
		*i = current;
		newline = 0;
	}
	return (newline);
}

void	execute_echo(t_minishell *minishell, int fd, t_cmd *cur)
{
	int	i;
	int	newline;
	int	file_fd;

	i = 1;
	(void)file_fd;
	if (cur->cmd[1])
		newline = check_newline(cur->cmd, cur->whitespace, &i);
	else
		newline = 1;
	while (cur->cmd[i] != NULL)
	{
		ft_putstr_fd(cur->cmd[i], fd);
		while (cur->whitespace[i] > 0)
		{
			ft_putstr_fd(" ", fd);
			cur->whitespace[i]--;
		}
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", fd);
	minishell->exit_code = 0;
}
