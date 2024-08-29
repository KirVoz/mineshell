/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:14 by aaleksee          #+#    #+#             */
/*   Updated: 2024/03/21 11:47:39 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;
	ssize_t		bytes_read;
	size_t		res_len;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(buffer, &bytes_read, fd);
	if (!buffer)
		return (NULL);
	result = get_line(&buffer, &res_len);
	if (bytes_read != 0)
		buffer = truncate_buffer(buffer, res_len);
	return (result);
}

char	*read_file(char *buffer, ssize_t *bytes_read, int fd)
{
	char	read_buffer[BUFFER_SIZE];

	if (!buffer)
	{
		*bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (*bytes_read <= 0)
			return (NULL);
		buffer = (char *)malloc((*bytes_read + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		ft_memcpy_gnl(buffer, read_buffer, *bytes_read);
	}
	while (!ft_strchr_gnl(buffer, '\n'))
	{
		buffer = append_to_buffer(buffer, fd, &bytes_read);
		if (*bytes_read <= 0)
			break ;
	}
	return (buffer);
}

char	*append_to_buffer(char *buffer, int fd, ssize_t **bytes_read)
{
	char	read_buffer[BUFFER_SIZE];
	char	*temp_buffer;
	ssize_t	temp_buffer_len;

	**bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	if (**bytes_read == 0)
		return (buffer);
	temp_buffer = ft_strjoin_gnl(buffer, read_buffer, **bytes_read);
	if (!temp_buffer)
	{
		free(buffer);
		return (NULL);
	}
	temp_buffer_len = ft_strlen_gnl(temp_buffer);
	free(buffer);
	buffer = (char *)malloc((temp_buffer_len + 1) * sizeof(char));
	if (!buffer)
	{
		free(temp_buffer);
		return (NULL);
	}
	ft_memcpy_gnl(buffer, temp_buffer, temp_buffer_len);
	free(temp_buffer);
	return (buffer);
}

char	*get_line(char **buffer, size_t *len)
{
	char	*newline;
	char	*res;

	newline = ft_strchr_gnl(*buffer, '\n');
	if (!newline)
	{
		res = ft_strjoin_gnl(*buffer, NULL, 0);
		free (*buffer);
		*buffer = NULL;
		return (res);
	}
	*len = newline - *buffer + 1;
	res = (char *)malloc((*len + 1) * sizeof(char));
	if (!res)
	{
		free (*buffer);
		*buffer = NULL;
		return (NULL);
	}
	ft_memcpy_gnl(res, *buffer, *len);
	return (res);
}

char	*truncate_buffer(char *buffer, size_t i)
{
	char	*truncated_buffer;
	size_t	new_buffer_len;

	if (!buffer)
		return (NULL);
	new_buffer_len = ft_strlen_gnl(&(buffer[i - 1]));
	if (new_buffer_len == 1)
	{
		free(buffer);
		buffer = NULL;
		return (buffer);
	}
	truncated_buffer = (char *)malloc((new_buffer_len) * sizeof(char));
	if (!truncated_buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	ft_memcpy_gnl(truncated_buffer, &(buffer[i]), new_buffer_len - 1);
	free(buffer);
	buffer = NULL;
	return (truncated_buffer);
}
/*
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int	a1 = open("41_with_nl.txt", O_RDONLY);
	int	a2 = open("42_with_nl.txt", O_RDONLY);
	int	a3 = open("43_with_nl.txt", O_RDONLY);

	char *b;
	b = get_next_line(a1); printf("%s", b); free(b);
	b = get_next_line(a2); printf("%s", b); free(b);
	b = get_next_line(a3); printf("%s", b); free(b);
	b = get_next_line(a1); printf("%s", b); free(b);
	b = get_next_line(a2); printf("%s", b); free(b);
	b = get_next_line(a3); printf("%s", b); free(b);
	
	close(a1);
	close(a2);
	close(a3);
}

#include <fcntl.h>
#include <stdio.h>
int	main()
{
	int	a = open("/Users/aleks/Desktop/42/
	get_next_line/alternate_line_nl_with_nl.txt", O_RDONLY);
	for (int i = 0; i < 10; i++)
	{
		char *m = get_next_line(a);
		free(m);
		printf("%s", m);
	}
	close(a);
}

#include <fcntl.h>
#include <stdio.h>
int	main()
{
	int	a = open("/Users/aleks/Desktop/42/
	get_next_line/alternate_line_nl_with_nl.txt", O_RDONLY);
	FILE *b = fopen("output.txt", "r");
	
	char *c;
	while ((c = get_next_line(a)) != NULL)
	{
		fprintf(b, "%s", c);
		free(c);
	}
	fclose(b);
	close(a);
}

#include <fcntl.h>
#include <stdio.h>
int	main()
{
	int	a = open("/Users/aleks/Desktop/42/
	get_next_line/big_line_no_nl.txt", O_RDONLY);
	FILE *b = fopen("output.txt", "w+");
	char *c;

	// while ((c = get_next_line(a)) != NULL)
	// {
	// 	fprintf(b, "%s", c);
	// 	free(c);
	// }
	
	c = get_next_line(a);
	printf("1 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);
		
	c = get_next_line(a);
	printf("2 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);

	c = get_next_line(a);
	printf("3 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);
		
	c = get_next_line(a);
	printf("4 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);

	c = get_next_line(a); // 5
	printf("5 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);
		
	c = get_next_line(a);
	printf("6 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);

	c = get_next_line(a);
	printf("7 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);
		
	c = get_next_line(a);
	printf("8 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);

	c = get_next_line(a); // 9
	printf("9 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);
		
	c = get_next_line(a); // 10
	printf("10 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);

	c = get_next_line(a); // 11
	printf("11 call:\n%s", c);
	fprintf(b, "%s", c);
	free(c);

	fclose(b);
	close(a);
}
*/
