/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 04:29:48 by aaleksee          #+#    #+#             */
/*   Updated: 2024/03/14 04:29:50 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define SPECS "cspdiuxX%"
# define HEX_L "0123456789abcdef"
# define HEX_U "0123456789ABCDEF"

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include "../../../includes/libft.h"

typedef struct s_format
{
	int		hash;
	int		ws;
	int		plus;
	char	specifier;
}	t_form;

int		ft_printf(const char *str, ...);
void	ft_putstr(const char *s, int **len);
void	ft_putchar(const char c, int **len);
void	ft_getnbr(int n, int **len, t_form *specs);
void	ft_putnbr(int n, int **len, t_form *specs);
void	ft_putlnbr(long int n, int **len, t_form *specs);
void	ft_put_unsigned_nbr(int n, int **len, t_form *specs);

void	write_address(void *address, int **len);
void	write_address_recursion(unsigned long address_int, int ***len);

void	ft_conversion_recursion(unsigned int num, char *base, int ***len);
void	ft_conversion(unsigned int num, char *base, int **len, t_form *specs);

void	flag_padding(int n, int ***len, t_form *specs);

t_form	*flags_initialisation(t_form *specs);

#endif
