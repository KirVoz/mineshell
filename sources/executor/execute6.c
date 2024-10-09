/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:33:03 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 19:43:56 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	handle_hd(t_cmd *current, int *last_input_fd)
{
	if (*last_input_fd != -1)
		close(*last_input_fd);
	heredoc_fd(current);
}

void	handle_output_file(t_minishell *minishell, t_list *tmp,
		int *last_output_fd, int flags)
{
	if (*last_output_fd != -1)
		close(*last_output_fd);
	*last_output_fd = open(tmp->filename, flags, 0644);
	open_file(minishell, tmp->filename, 1);
}

void	handle_input_file(t_minishell *minishell, t_list *tmp,
		int *last_input_fd)
{
	if (*last_input_fd != -1)
		close(*last_input_fd);
	*last_input_fd = open(tmp->filename, O_RDONLY);
	open_file(minishell, tmp->filename, 0);
	if (*last_input_fd == -1)
	{
		no_file(minishell, tmp->filename);
		exit(minishell->exit_code);
	}
}
