/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_p_x.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:50:19 by aaleksee          #+#    #+#             */
/*   Updated: 2024/04/23 19:50:22 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_address_recursion(unsigned long address_int, int ***len)
{
	if (address_int > 0)
	{
		write_address_recursion(address_int / 16, len);
		write(1, &(HEX_L[address_int % 16]), 1);
		(***len)++;
	}
}

void	write_address(void *address, int **len)
{
	unsigned long	address_int;

	address_int = (unsigned long)address;
	write(1, "0x", 2);
	**len += 2;
	if (address_int == 0)
	{
		write(1, "0", 1);
		(**len)++;
	}
	else
		write_address_recursion(address_int, &len);
}

void	ft_conversion_recursion(unsigned int num, char *base, int ***len)
{
	size_t	base_len;
	int		quotient;
	int		remainder;

	base_len = ft_strlen(base);
	if (num != 0)
	{
		quotient = num / base_len;
		remainder = num % base_len;
		ft_conversion_recursion(quotient, base, len);
		write(1, &(base[remainder]), 1);
		(***len)++;
	}
}

void	ft_conversion(unsigned int num, char *base, int **len, t_form *specs)
{
	if (num == 0)
	{
		write(1, "0", 1);
		(**len)++;
		return ;
	}
	if (specs->hash == 1)
	{
		write(1, "0", 1);
		write(1, &(specs->specifier), 1);
		(**len) += 2;
	}
	ft_conversion_recursion(num, base, &len);
}
