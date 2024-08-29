/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 02:21:11 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 16:39:21 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char const c, char const *set);
static int	ft_start(char const *s1, char const *set);
static int	ft_end(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		start_i;
	int		end_i;
	int		trim_i;
	int		trim_len;

	if (!s1 || !set)
		return (NULL);
	start_i = ft_start(s1, set) - 1;
	if (start_i == -1)
	{
		trimmed = (char *)malloc(1 * sizeof(char));
		trimmed[0] = '\0';
		return (trimmed);
	}
	end_i = ft_end(s1, set) + 1;
	trim_i = 0;
	trim_len = end_i - start_i + 1;
	trimmed = (char *)malloc((trim_len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	while (trim_i < trim_len)
		trimmed[trim_i++] = s1[start_i++];
	trimmed[trim_i] = '\0';
	return (trimmed);
}

static int	ft_inset(char const c, char const *set)
{
	int	set_i;

	set_i = 0;
	while (set[set_i] != '\0')
	{
		if (c == set[set_i])
			return (1);
		set_i++;
	}
	return (0);
}

static int	ft_start(char const *s1, char const *set)
{
	int	inset;
	int	start_i;

	inset = 1;
	start_i = 0;
	while (inset != 0 && s1[start_i] != '\0')
	{
		inset = ft_inset(s1[start_i], set);
		start_i++;
	}
	if (s1[start_i] == '\0')
		return (0);
	return (start_i);
}

static int	ft_end(char const *s1, char const *set)
{
	int	inset;
	int	end_i;

	inset = 1;
	end_i = ft_strlen(s1) - 1;
	while (inset != 0)
	{
		inset = ft_inset(s1[end_i], set);
		end_i--;
	}
	return (end_i);
}
/*
#include <stdio.h>

int main()
{
	char *s = ft_strtrim("   xxx   xxx", " x");
	printf("%s", s);
	// char *s = "  \t \t \n   \n\n\n\t";
	// printf("%s\n", ft_strtrim(s, " \n\t");
	// printf("%s\n", ft_strtrim("abqsbc", "abc"));
	// printf("%s\n", ft_strtrim("xavocadoyz", "xyz"));
	// printf("%s\n", ft_strtrim("yavocadoyz", "yz"));
	// printf("%s\n", ft_strtrim("xavocadox", "x"));
}
*/
