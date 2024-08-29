/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:14 by aaleksee          #+#    #+#             */
/*   Updated: 2024/03/21 11:50:51 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	tmp = (char *)s;
	while (tmp[++i] != '\0')
	{
		if (tmp[i] == (char)c)
			return (&tmp[i]);
	}
	return (NULL);
}

void	*ft_memcpy_gnl(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_data;
	char	*src_data;

	i = 0;
	if (!dst && !src)
		return (dst);
	dst_data = (char *)dst;
	src_data = (char *)src;
	while (i < n)
	{
		dst_data[i] = src_data[i];
		i++;
	}
	dst_data[i] = '\0';
	return (dst);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2, ssize_t bytes_read)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*joined_str;

	i = -1;
	len_s1 = ft_strlen_gnl(s1);
	len_s2 = bytes_read;
	joined_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	ft_memcpy_gnl(joined_str, s1, len_s1);
	while (++i < len_s2)
		joined_str[len_s1 + i] = s2[i];
	joined_str[len_s1 + len_s2] = '\0';
	return (joined_str);
}
