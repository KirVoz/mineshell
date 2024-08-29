/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:14 by aaleksee          #+#    #+#             */
/*   Updated: 2024/03/13 12:51:48 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*read_file(char *buffer, ssize_t *bytes_read, int fd);
char	*append_to_buffer(char *buffer, int fd, ssize_t **bytes_read);
char	*get_line(char **buffer, size_t *len);
char	*truncate_buffer(char *buffer, size_t i);
char	*ft_strjoin_gnl(char const *s1, char const *s2, ssize_t bytes_read);
void	*ft_memcpy_gnl(void *dst, const void *src, size_t n);
char	*ft_strchr_gnl(const char *s, int c);
size_t  ft_strlen_gnl(const char *s);

#endif
