/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 03:23:58 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/22 14:38:46 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*ptr;

	if (n == 0)
		return ;
	i = 0;
	ptr = (char *)s;
	while (i < n)
		ptr[i++] = '\0';
}
/*
int	main()
{
	char	s[] = "AAAAAAAAA";
	ft_bzero(s, 3);
}
*/
