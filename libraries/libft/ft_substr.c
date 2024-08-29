/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 02:30:30 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 15:39:20 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (!s)
		return (NULL);
	i = 0;
	if (start + len > ft_strlen(s))
		if (((int)ft_strlen(s)) - (int)start > 0)
			len = ft_strlen(s) - start;
	if ((start >= ft_strlen(s)) || len == 0)
	{
		substr = (char *)malloc(ft_strlen(s) + 1);
		substr[i] = '\0';
		return (substr);
	}
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *s = ft_substr("tripouille", 100, 1);
    printf("%s\n", s);
	free(s);
}
*/
