/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_str_nbr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:50:19 by aaleksee          #+#    #+#             */
/*   Updated: 2024/04/23 19:50:22 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(const char *s, int **len)
{
	int	i;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		(**len) += 6;
		return ;
	}
	i = -1;
	while (s[++i] != 0)
	{
		write(1, &s[i], 1);
		(**len)++;
	}
}

void	ft_putchar(const char c, int **len)
{
	write(1, &c, 1);
	(**len)++;
}

void	ft_putnbr(int n, int **len, t_form *specs)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648", len);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', len);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, len, specs);
		n = n % 10;
	}
	ft_putchar(n + '0', len);
}

void	ft_putlnbr(long int n, int **len, t_form *specs)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10, len, specs);
		n = n % 10;
	}
	ft_putchar(n + '0', len);
}

void	ft_put_unsigned_nbr(int n, int **len, t_form *specs)
{
	long int	unsigned_nbr;

	unsigned_nbr = (unsigned int)n;
	ft_putlnbr(unsigned_nbr, len, specs);
}
