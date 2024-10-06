/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:24:11 by aaleksee          #+#    #+#             */
/*   Updated: 2024/10/02 10:24:12 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	numeric_error(t_minishell *minishell, char *cmd, char *arg)
{
	char	*error;

	error = construct_error(cmd, arg, ": numeric argument required\n", 's');
	ft_putstr_fd(error, 2);
	free(error);
	minishell->exit_code = 255;
	if (minishell->tmp->is_child != 0)
		exit(minishell->exit_code);
}

void	deleted_dir(t_minishell *minishell)
{
	char	*error;

	error = construct_error("cd: error retrieving current directory: ",
			"getcwd: cannot access parent directories: ",
			"No such file or directory\n", 'e');
	ft_putstr_fd(error, 2);
	free(error);
	minishell->exit_code = 1;
	if (minishell->tmp->is_child != 0)
		exit(minishell->exit_code);
}
