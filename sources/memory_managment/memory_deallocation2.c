/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_deallocation2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 05:33:48 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/30 05:33:49 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	free_array(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
}

void	free_heredoc_tmp(char ***heredoc_tmp)
{
	int	i;

	i = 0;
	if (!heredoc_tmp)
		return ;
	while (heredoc_tmp[i])
	{
		free_array(heredoc_tmp[i]);
		i++;
	}
	free(heredoc_tmp);
}
