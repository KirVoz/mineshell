/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:08:37 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 14:47:37 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	j;

	if (!src && size != 0)
		return (src[0]);
	if (!dst && size != 0)
		return (dst[0]);
	if (!dst && size == 0)
		return (size + ft_strlen(src));
	len = ft_strlen(dst) + ft_strlen(src);
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	i = ft_strlen(dst);
	j = 0;
	while ((i < size - 1) && src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (len);
}
/*
#include <string.h>
#include <stdio.h>

int main()
{
	char b[0xF] = "nyan !";
	printf("std: %zu\n", ft_strlcat(((void *)0), b, 0));
	printf("my: %zu\n", strlcat(((void *)0), b, 0));

	// char d[0xF] = "nyan !";
	// char e[0xF] = "nyan !";

	// printf("%s %s\n", d, e);
	// printf("my: %zu\n", ft_strlcat(e, ((void *)0), 2));
	// printf("%s %s\n", d, e);
	// printf("std: %zu\n", strlcat(e, ((void *)0), 2));
	// printf("%s %s\n", d, e);
	// // printf("std: %zu\n", ft_strlcat(((void *)0), d, 0));
	// // printf("%s %s\n", d, e);
	char a[20] = "aaaa.aaaa.aaaa.aaaa.";
	char b[] = "a";
	char c[20] = "aaaa.aaaa.aaaa.aaaa.";
	char d[] = "a";
	// char a[20] = "a";
	// char b[] = "aaaa.aaaa.aaaa.aaaa.";
	// char c[20] = "a";
	// char d[] = "aaaa.aaaa.aaaa.aaaa.";
	// char a[20] = "";
	// char b[] = "";
	// char c[20] = "";
	// char d[] = "";

	printf("%s\n", a);
	printf("my: %zu\n", ft_strlcat(a, b, 20));
	printf("%s\n", a);
	printf("std: %zu\n", strlcat(c, d, 20));
	printf("%s\n", c);
}
*/
