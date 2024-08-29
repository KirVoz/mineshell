/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 01:09:10 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 15:14:07 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s3;
	const unsigned char	*s4;

	i = -1;
	s3 = s1;
	s4 = s2;
	while (++i < n)
		if (s3[i] != s4[i])
			return (s3[i] - s4[i]);
	return (0);
}
/*
int main() 
{
    const char a[] = "Hello";
    const char b[] = "Hallo";

    int c = ft_memcmp(a, b, 4);
	printf("%d\n", c);

	printf("a\n");

    const char d[] = "Hello";
    const char e[] = "Hallo";

    int f = memcmp(d, e, 4);
	printf("%d\n", f);

	const char a[] = "a";
    const char b[] = "";

    int c = ft_memcmp(a, b, 4);
	printf("%d\n", c);

	printf("a\n");

    const char d[] = "a";
    const char e[] = "";

    int f = memcmp(d, e, 4);
	printf("%d\n", f);
}
*/
