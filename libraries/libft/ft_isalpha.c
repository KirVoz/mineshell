/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 02:10:09 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 13:34:58 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
int	main()
{
	printf("%d\n", ft_isalpha(1));
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", ft_isalpha('G'));
}
*/
