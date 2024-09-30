/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:10:15 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/30 19:29:49 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fail(const char *exit_message)
{
	perror(exit_message);
	exit(EXIT_FAILURE);
}

void	not_found(t_minishell *minishell, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	minishell->exit_code = 127;
}

void	no_file(t_minishell *minishell, char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	minishell->exit_code = 1;
}

void	no_path_file(t_minishell *minishell, char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	minishell->exit_code = 127;
}

void	not_valid(t_minishell *minishell, char *cmd)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	minishell->exit_code = 1;
}