/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:09:11 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/18 21:12:33 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (s1[i] - s2[i]);
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i] && s1[i] == '\0')
			return (-1);
		if (s1[i] != s2[i] && s2[i] == '\0')
			return (1);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	// printf("std t, empty, 0 - %d\n",  strncmp("t", "", 0));
	// printf("std Tripouille, TripouilleX, 42 - %d\n", 
	// strncmp("Tripouille", "TripouilleX", 42));
	// printf("std Tripouille, Tripouill, 42 - %d\n", 
	// strncmp("Tripouille", "Tripouill", 42));
	// printf("std empty, 1, 0 - %d\n", strncmp("", "1", 0));
	// printf("std 1, empty, 0 - %d\n\n", strncmp("1", "", 0));


	// printf("my t, empty, 0 - %d\n",  ft_strncmp("t", "", 0));
	// printf("my Tripouille, TripouilleX, 42 - %d\n", 
	// ft_strncmp("Tripouille", "TripouilleX", 42));
	// printf("my Tripouille, Tripouill, 42 - %d\n", 
	// ft_strncmp("Tripouille", "Tripouill", 42));
	// printf("my empty, 1, 0 - %d\n", ft_strncmp("", "1", 0));
	// printf("my 1, empty, 0 - %d\n", ft_strncmp("1", "", 0));
	char a[] = "\200";
	char b[] = "\0";
	printf("my:  - %d\n", ft_strncmp(a, b, 3));
	printf("std: - %d\n", strncmp(a, b, 3));
}
*/