/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:25:42 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:25:43 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	is_pipe(char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	if ((ft_strlen(token) != 0) && ft_strncmp(token, "|", token_len) == 0)
		return (1);
	return (0);
}

int	is_redirection(char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	if ((ft_strlen(token) != 0) && (ft_strncmp(token, "<", token_len) == 0
			|| ft_strncmp(token, ">", token_len) == 0
			|| ft_strncmp(token, "<<", token_len) == 0
			|| ft_strncmp(token, ">>", token_len) == 0))
		return (1);
	return (0);
}

void	handle_redirections(t_cmd *current, char *delimiter, char *file)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	if (ft_strncmp(delimiter, "<", delimiter_len) == 0)
		ft_lstadd_back(&current->files,
			ft_lstnew(ft_strdup(file), 'i'));
	else if (ft_strncmp(delimiter, ">", delimiter_len) == 0)
		ft_lstadd_back(&current->files,
			ft_lstnew(ft_strdup(file), 'o'));
	else if (ft_strncmp(delimiter, ">>", delimiter_len) == 0)
		ft_lstadd_back(&current->files,
			ft_lstnew(ft_strdup(file), 'a'));
}
