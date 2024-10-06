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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": too many arguments", 2);
	ft_putstr_fd("\n", 2);
	minishell->exit_code = 1;
	if (minishell->tmp->is_child != 0)
		exit(minishell->exit_code);
}

int	syntax_error(t_minishell *minishell, char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	minishell->exit_code = 258;
	if (minishell->tmp->is_child != 0)
		exit(minishell->exit_code);
	return (0);
}

void	exe_binary_error(t_minishell *minishell, char *path)
{
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": cannot execute binary file\n", 2);
	minishell->exit_code = 126;
	
}

void	is_a_directory(t_minishell *minishell, char *path, char mode)
{
	if (mode == 'm')
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd("/: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("/: is a directory\n", 2);
	}
	else if (mode == 'e')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);		
	}
	minishell->exit_code = 126;
}

void	permission_denied(t_minishell *minishell, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	minishell->exit_code = 126;
}