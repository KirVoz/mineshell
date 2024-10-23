/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:33:03 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 19:43:56 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static long long	check_overflow(long long res, int sign, char next_digit)
{
	if (sign == 1 && (res > (LLONG_MAX - (next_digit - '0')) / 10))
		errno = ERANGE;
	if (sign == -1 && (res > (-(LLONG_MIN + (next_digit - '0')) / 10)))
		errno = ERANGE;
	return (res);
}

long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	errno = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = check_overflow(res, sign, *str);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

int	is_valid_number(const char *str)
{
	int	sign_count;

	sign_count = 0;
	if (ft_isalpha(*str))
		return (0);
	while (*str)
	{
		if (*str == '-' || *str == '+')
		{
			sign_count++;
			if (sign_count > 1)
				return (0);
		}
		else if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
