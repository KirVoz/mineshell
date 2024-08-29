/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:08:26 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 14:46:04 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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
	dst[copy_len] = '\0';
	return (src_len);
}
/*
#include <stdio.h>

int	main()
{
	char a[] = "Hello";
	char b[20];

	printf("7, %zu\n", ft_strlcpy(b, a, 7));
	printf("%s\n", b);	
	printf("%c\n", b[4]);	
	printf("%c\n", b[5]);	
	printf("6, %zu\n", ft_strlcpy(b, a, 6));
	printf("%s\n", b);	
	printf("5, %zu\n", ft_strlcpy(b, a, 5));
	printf("%s\n", b);
	printf("4, %zu\n", ft_strlcpy(b, a, 4));
	printf("%s\n", b);

}
*/
