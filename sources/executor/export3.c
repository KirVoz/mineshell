/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:38 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:47:28 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < n)
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*find_var_name(char *cmd)
{
	char*	plus;
	size_t	len;
	char	*res;

	plus = ft_strchr(cmd, '+');
	if (!plus)
		return (NULL);
	len = plus - cmd;
	res = ft_strndup(cmd, len);
	return (res);
}

void	*ft_strcat(char *dst, const char *src)
{
	char *dst_start;

	dst_start = dst;
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_start);
}
