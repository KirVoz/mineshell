/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:09:58 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/30 05:10:00 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_count_error(t_minishell *minishell, char *command)
{
	char	*error;

	error = construct_error(command, ": too many arguments\n", NULL, 0);
	ft_putstr_fd(error, 2);
	free(error);
	minishell->exit_code = 1;
	if (minishell->tmp->is_child != 0)
		exit(minishell->exit_code);
}

int	syntax_error(t_minishell *minishell, char *token)
{
	char	*error;

	error = construct_error("syntax error near unexpected token `",
			token, "\n", 0);
	ft_putstr_fd(error, 2);
	free(error);
	minishell->exit_code = 258;
	return (0);
}

void	exe_binary_error(t_minishell *minishell, char *path)
{
	char	*error;

	error = construct_error(path, path, ": cannot execute binary file\n", 's');
	ft_putstr_fd(error, 2);
	free(error);
	minishell->exit_code = 126;
}

void	is_a_directory(t_minishell *minishell, char *path, char mode)
{
	char	*error;

	if (mode == 'm')
	{
		error = construct_error(path, path, "/: is a directory\n", mode);
		ft_putstr_fd(error, 2);
		free(error);
	}
	else if (mode == 'e')
	{
		error = construct_error(path, ": is a directory\n", NULL, 0);
		ft_putstr_fd(error, 2);
		free(error);
	}
	minishell->exit_code = 126;
}

void	permission_denied(t_minishell *minishell, char *path)
{
	char	*error;

	error = construct_error(path, ": Permission denied\n", NULL, 0);
	ft_putstr_fd(error, 2);
	free(error);
	minishell->exit_code = 126;
}