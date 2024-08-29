/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:10:17 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 15:36:11 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;

	if (count == 0 || size == 0)
	{
		res = (char *)malloc(count * size);
		return ((void *)res);
	}
	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	if (count * size > SIZE_MAX / count)
		return (NULL);
	res = (char *)malloc(count * size);
	if (!res)
		return (NULL);
	ft_bzero(res, count * size);
	return ((void *)res);
}
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
	void	*a = ft_calloc(SIZE_MAX, SIZE_MAX);
	free(a);
	int size = 8539;
	void	*d2 = calloc(size, sizeof(int));
	void	*d1 = ft_calloc(size, sizeof(int));
	for (int i = 0; i < 10; i++)
	{
		printf("%c - ", ((char *)d2)[i]);
		printf("%p\n",((char **)&d2)[i]);
		printf("\n");
	}
	for (int i = 0; i < 10; i++)
	{
		printf("my");
		printf("%c - ", ((char *)d1)[i]);
		printf("%p\n", ((char **)&d1)[i]);
		printf("\n");
	}
	printf("%d\n", memcmp(d1, d2, size * sizeof(int)));
	free(d1);
	free(d2);
}
*/
