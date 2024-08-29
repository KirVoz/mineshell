/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:50:19 by aaleksee          #+#    #+#             */
/*   Updated: 2024/04/23 19:50:22 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_form	*flags_initialisation(t_form *specs)
{
	specs->hash = 0;
	specs->ws = 0;
	specs->plus = 0;
	specs->specifier = '0';
	return (specs);
}

void	flag_padding(int n, int ***len, t_form *specs)
{
	if (specs->ws == 1 && specs->plus != 1)
	{
		if (n >= 0)
		{
			write(1, " ", 1);
			(***len)++;
			return ;
		}
	}
	if (specs->plus == 1)
	{
		if (n >= 0)
		{
			write(1, "+", 1);
			(***len)++;
			return ;
		}
	}
}

void	ft_getnbr(int n, int **len, t_form *specs)
{
	flag_padding(n, &len, specs);
	ft_putnbr(n, len, specs);
}
