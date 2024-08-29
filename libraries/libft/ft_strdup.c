/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:10:34 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 15:36:55 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	size_t		i;
	char		*res;

	len = ft_strlen(s1);
	i = 0;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

int		main()
{
	char	str1[] = "lorem ipsum dolor sit amet";
	char	str2[] = "lorem ipsum dolor sit amet";
	// char	*str_dup;

	// if (!(str_dup = ft_strdup(str2)))
	// 	ft_print_result("NULL");
	// else
	// 	ft_print_result(str_dup);
	// if (str_dup == str2)
	// 	ft_print_result("\nstr_dup's adress == str's adress");
	// return (0);
	printf("%s\n", strdup(str1));
	printf("%s\n", ft_strdup(str2));
}*/
