/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 04:18:27 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/14 12:44:30 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_len_sign(int n, int *len, int *sign);
static char	*ft_minint(char **res, int n, int len);

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*res;

	ft_len_sign(n, &len, &sign);
	if (n == -2147483648)
		return (ft_minint(&res, n - 1, len));
	if (n < 0)
	{
		len += 1;
		n *= -1;
	}
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (--len >= 0)
	{
		res[len] = n % 10 + '0';
		n /= 10;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}

static char	*ft_minint(char **res, int n, int len)
{
	*res = (char *)malloc((len + 2) * sizeof(char));
	if (!(*res))
		return (NULL);
	(*res)[len + 1] = '\0';
	(*res)[len] = 8 + '0';
	n /= 10;
	while (--len >= 0)
	{
		(*res)[len] = n % 10 + '0';
		n /= 10;
	}
	(*res)[0] = '-';
	return (*res);
}

static void	ft_len_sign(int n, int *len, int *sign)
{
	*sign = 1;
	if (n < 0)
	{
		*sign = -1;
		*len = 1;
	}
	*len = 0;
	while (n != 0)
	{
		(*len)++;
		n = n / 10;
	}
	if (*len == 0)
		*len = 1;
	return ;
}
/*
#include "stdio.h"

int main()
{
	int size = 10;
	char *res[size];
	res[0] = ft_itoa(1);
	res[1] = ft_itoa(2147483647);
	res[2] = ft_itoa(-9999);
	res[3] = ft_itoa(-623);
	res[4] = ft_itoa(156);
	res[5] = ft_itoa(0);
	res[6] = ft_itoa(-0);
	res[7] = ft_itoa(-2147483648);
	res[8] = ft_itoa(-123);
	res[9] = ft_itoa(-1);
	for (int i = 0; i < size; i++)
	{
		printf("%s\n", res[i]);
		free(res[i]);
	}
}
*/