/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:15:05 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 16:22:33 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		join_i;
	int		source_i;
	int		len_s1;
	int		len_s2;
	char	*joined_str;

	if (!s1 || !s2)
		return (NULL);
	join_i = 0;
	source_i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined_str = (char *)malloc(len_s1 + len_s2 + 1);
	if (!joined_str)
		return (NULL);
	while (join_i < len_s1)
		joined_str[join_i++] = s1[source_i++];
	source_i = 0;
	while (join_i < len_s1 + len_s2)
		joined_str[join_i++] = s2[source_i++];
	joined_str[join_i] = '\0';
	return (joined_str);
}
/*
#include <stdio.h>
int	main()
{
	char a[] = "He";
	char b[] = "1";
	char *d = ft_strjoin(a, b);
	printf("%s", d);
}
*/
