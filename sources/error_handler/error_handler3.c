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

void	handle_incorrect_arguments(t_minishell *minishell, char *av)
{
	struct stat	stat_buf;

	stat(av, &stat_buf);
	if (get_path(minishell, av) && !S_ISDIR(stat_buf.st_mode))
		exe_binary_error(minishell, get_path(minishell, av));
	else if (access(av, F_OK) == 0 && S_ISDIR(stat_buf.st_mode))
		is_a_directory(minishell, av, 'm');
	else
		no_path_file(minishell, av);
}

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
