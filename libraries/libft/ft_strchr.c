/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:08:51 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 15:02:10 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	tmp = (char *)s;
	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == (char)c)
			return (&tmp[i]);
		i++;
	}
	if (c == '\0')
		return (&tmp[i]);
	return (NULL);
}
/*
#include <stdio.h>
int	main()
{
	char s[] = "Hello";
	int	c = '\0';
	printf("%s\n", ft_strchr(s, c));
	printf("%p\n", &s[5]);
	printf("%p\n", ft_strchr(s, c));
}
*/
