/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:09:28 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 15:13:26 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		if (((const unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)&s[i]);
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
	printf("%p\n", memchr(tab, -1, 7));
	printf("%p\n", ft_memchr(tab, -1, 7));
}

#include <stdio.h>
#include <string.h>
int main()
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	printf("%p\n", (void *)&s[2]);
	printf("%p\n", ft_memchr(s, 2 + 256, 3));
	printf("%p\n", memchr(s, 2 + 256, 3));
    const char a[] = "";
    int b = 'l';

    const char *c = ft_memchr(a, b, 4);
	printf("%s\n", c);

	const char d[] = "";
    int e = 'l';

    const char *f = ft_memchr(d, e, 4);
	printf("%s\n", f);
}
*/
