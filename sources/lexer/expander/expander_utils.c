/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:54 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:24:55 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

size_t	strlcpy_eq(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	copy_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	copy_len = dstsize - 1;
	if (copy_len > src_len)
		copy_len = src_len;
	ft_memcpy(dst, src, copy_len);
	dst[copy_len] = '=';
	dst[copy_len + 1] = '\0';
	return (src_len);
}

char	*allocate_dup(char *dup, char *error)
{
	char	*result;

	result = ft_strdup(dup);
	if (!result)
		exit_fail(error);
	return (result);
}

char	set_quote(char c, int *in_quote)
{
	*in_quote = 1;
	return (c);
}

void	write_exit_code(char **result, char *exit_code, int *i)
{
	while (*exit_code)
	{
		(*result)[*i] = *exit_code;
		(*i)++;
		exit_code++;
	}
}

void	digit_env_var_substitute(char **token, char **result, int *i)
{
	*token += 2;
	while (**token && !(**token == ' ' || **token == '"'
			|| **token == '\''))
	{
		(*result)[*i] = *(*token)++;
		(*i)++;
	}
}
