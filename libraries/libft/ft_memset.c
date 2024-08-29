/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 02:29:23 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 14:37:53 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = -1;
	ptr = (unsigned char *)b;
	while (++i != len)
		ptr[i] = c;
	return (b);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char str[50];
	char str1[50];
	
	strcpy(str,"Memset function\n");
	strcpy(str1,"Memset function\n");
	printf("Bfr:  %s", str);
	memset(str,'$', 5);
	ft_memset(str1,'$', 5);
	printf("Std:  %s", str);
	printf("Mine: %s", str1);
}
*/
