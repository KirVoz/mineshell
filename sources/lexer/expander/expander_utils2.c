/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:16:26 by aaleksee          #+#    #+#             */
/*   Updated: 2024/10/31 21:16:28 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	check_before_tilde(const char *token, char mode)
{
	char	*ptr;

	if (mode == 's')
		ptr = ft_strnstr(token, "~/", ft_strlen(token));
	if (mode == 'd')
		ptr = ft_strnstr(token, "~:", ft_strlen(token));
	if (ptr)
	{
		if (ptr == token || ft_isspace(*(ptr - 1)))
			return (1);
	}
	return (0);
}

char	*tilda_alloc_init(char *token)
{
	char	*result;

	result = allocate_string(ft_strlen(token) - 1 + 5, "Tilda_alloc_init");
	result[0] = '\0';
	return (result);
}
