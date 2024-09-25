/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:25:16 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:25:18 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	delimiter_counter(char **token, int *pipes, int *right_redirs,
		int *left_redirs)
{
	*pipes = 0;
	*right_redirs = 0;
	*left_redirs = 0;
	while (*token && ft_strchr(DELIMS, **token))
	{
		if (**token == '|')
			(*pipes)++;
		else if (**token == '>')
			(*right_redirs)++;
		else if (**token == '<')
			(*left_redirs)++;
		token++;
	}
}

int	tokens_counter(char **tokens)
{
	int	count;

	count = 0;
	while (*tokens)
	{
		if (!ft_strchr("", **tokens))
			count++;
		tokens++;
	}
	return (count);
}
