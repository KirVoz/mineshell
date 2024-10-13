/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:27 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:39:10 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	ft_free_exe_free(t_minishell *minishell, t_cmd *current)
{
	free(minishell->path);
	minishell->path = NULL;
	execve(get_path(minishell, current->cmd[0]),
		current->cmd, minishell->env);
	free(minishell->path);
	minishell->path = NULL;
}
