/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:09:02 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 15:04:26 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	tmp = (char *)s;
	i = ft_strlen(s);
	if (c == '\0')
		return (&tmp[i]);
	while (--i >= 0)
		if (tmp[i] == (char)c)
			return (&tmp[i]);
	return (NULL);
}
/*
#include <stdio.h>
int	main()
{
	char s[] = "Hello";
	int	c = '\0';
	printf("%s\n", ft_strrchr(s, c));
	printf("%p\n", &s[5]);
	printf("%p\n", ft_strrchr(s, c));
}
*/
