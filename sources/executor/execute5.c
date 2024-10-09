/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:33:03 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 19:43:56 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	handle_file_modes(t_minishell *minishell, t_cmd *current, t_list *tmp,
		t_in_out *input)
{
	if (tmp->mode == 'h')
		handle_hd(current, &input->in);
	else if (tmp->mode == 'o')
		handle_output_file(minishell, tmp, &input->out,
			O_WRONLY | O_CREAT | O_TRUNC);
	else if (tmp->mode == 'a')
		handle_output_file(minishell, tmp, &input->out,
			O_WRONLY | O_CREAT | O_APPEND);
	else if (tmp->mode == 'i')
		handle_input_file(minishell, tmp, &input->in);
}

void	process_files(t_minishell *minishell, t_cmd *current, t_in_out *input)
{
	t_list	*tmp;

	tmp = current->files;
	while (tmp)
	{
		handle_file_modes(minishell, current, tmp, input);
		tmp = tmp->next;
	}
}

void	duplicate_input_fd(t_minishell *minishell, int last_input_fd, int i)
{
	if (last_input_fd != -1)
	{
		dup2(last_input_fd, STDIN_FILENO);
		close(last_input_fd);
	}
	else if (i > 0)
		dup2(minishell->pipes[i - 1][0], STDIN_FILENO);
}

void	duplicate_output_fd(t_minishell *minishell, int last_output_fd, int i,
		int num_cmd)
{
	if (last_output_fd != -1)
	{
		dup2(last_output_fd, STDOUT_FILENO);
		close(last_output_fd);
	}
	else if (i < num_cmd - 1)
		dup2(minishell->pipes[i][1], STDOUT_FILENO);
}

void	redirects(t_minishell *minishell, t_cmd *current, int i, int num_cmd)
{
	t_in_out	tmp;

	tmp.in = -1;
	tmp.out = -1;
	process_files(minishell, current, &tmp);
	duplicate_input_fd(minishell, tmp.in, i);
	duplicate_output_fd(minishell, tmp.out, i, num_cmd);
}
