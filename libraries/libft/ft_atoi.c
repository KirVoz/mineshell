/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:10:00 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/13 13:57:15 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char s);
static int	ft_len(const char *num_str);
static int	ft_power(int pow);

int	ft_atoi(const char *str)
{
	size_t			i;
	int				len;
	int				sign;
	long long int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		len = ft_len(&str[i]);
		res += (str[i] - '0') * ft_power(len - 1);
		i++;
	}
	return (res * sign);
}

static int	ft_power(int pow)
{
	int	num;

	num = 10;
	if (pow == 0)
		return (1);
	while (pow != 1)
	{
		num = num * 10;
		pow--;
	}
	return (num);
}

static int	ft_len(const char *num_str)
{
	int	i;

	i = 0;
	while (ft_isdigit(num_str[i]))
		i++;
	return (i);
}

static int	ft_isspace(char s)
{
	if ((s >= 9 && s <= 13) || s == 32)
		return (1);
	return (0);
}
/*
#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("std %d,\n", atoi(""));
	printf("my %d,\n", ft_atoi(""));
	printf("___\n");
	printf("std %d,\n", atoi("1a"));
	printf("my %d,\n", ft_atoi("1a"));
	printf("___\n");
	printf("std %d,\n", atoi(" 1"));
	printf("my %d,\n", ft_atoi(" 1"));
	printf("___\n");
	printf("std %d,\n", atoi("-11"));
	printf("my %d,\n", ft_atoi("-11"));
	printf("___\n");
	printf("std %d,\n", atoi("-11a1"));
	printf("my %d,\n", ft_atoi("-11a1"));
	printf("___\n");
	printf("std %d,\n", atoi(" - 1"));
	printf("my %d,\n", ft_atoi(" - 1"));
	printf("___\n");
	printf("std %d,\n", atoi("+1234"));
	printf("my %d,\n", ft_atoi("+1234"));
	printf("___\n");
	printf("std %d,\n", atoi(" +1"));
	printf("my %d,\n", ft_atoi(" +1"));
	printf("___\n");
	printf("std %d,\n", atoi("	1"));
	printf("my %d,\n", ft_atoi("	1"));
	printf("___\n");
	printf("std %d,\n", atoi("	-+-1"));
	printf("my %d,\n", ft_atoi("	-+-1"));
}
*/