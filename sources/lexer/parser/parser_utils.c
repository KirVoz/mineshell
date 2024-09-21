#include "lexer.h"
#include "minishell.h"

int	if_pipe(char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	if ((ft_strlen(token) != 0) && ft_strncmp(token, "|", token_len) == 0)
		return (1);
	return (0);
}

int	is_redirection(char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	if ((ft_strlen(token) != 0) && (ft_strncmp(token, "<", token_len) == 0
		|| ft_strncmp(token, ">", token_len) == 0
		|| ft_strncmp(token, "<<", token_len) == 0
		|| ft_strncmp(token, ">>", token_len) == 0))
		return (1);
	return (0);
}

size_t	strlcat_delim(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	j;

	if (!src && size != 0)
		return (src[0]);
	if (!dst && size != 0)
		return (dst[0]);
	if (!dst && size == 0)
		return (size + ft_strlen(src));
	len = ft_strlen(dst) + ft_strlen(src);
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	i = ft_strlen(dst);
	dst[i++]= '-';
	j = 0;
	while ((i < size - 1) && src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (len);
}

void	store_skipped_infiles(t_cmd **current)
{
	char	*skipped_in;
	size_t	len;

	len = 0;
	skipped_in = (*current)->skipped_in;
	if (!skipped_in)
	{
		skipped_in = ft_strdup((*current)->infile);
		if (!skipped_in)
			exit_fail("Failed to allocate memory for skipped_in");
	}
	else
	{
		len += ft_strlen(skipped_in) + ft_strlen((*current)->infile) + 2;
		skipped_in = (char *)ft_realloc(skipped_in, ft_strlen(skipped_in)
			* sizeof(char), len * sizeof(char));
		if (!skipped_in)
			exit_fail("Failed to reallocate memory for skipped_in");
		strlcat_delim(skipped_in, (*current)->infile, len);
	}
	(*current)->skipped_in = skipped_in;
}

void	store_skipped_outfiles(t_cmd **current)
{
	char	*skipped_out;
	size_t	len;

	len = 0;
	skipped_out = (*current)->skipped_out;
	if (!skipped_out)
	{
		skipped_out = ft_strdup((*current)->outfile);
		if (!skipped_out)
			exit_fail("Failed to allocate memory for skipped_out");
	}
	else
	{
		len += ft_strlen(skipped_out) + ft_strlen((*current)->outfile) + 2;
		skipped_out = (char *)ft_realloc(skipped_out, ft_strlen(skipped_out)
			* sizeof(char), len * sizeof(char));
		if (!skipped_out)
			exit_fail("Failed to reallocate memory for skipped_out");
		strlcat_delim(skipped_out, (*current)->outfile, len);
	}
	(*current)->skipped_out = skipped_out;
}

void	handle_redirections(t_cmd *current, char *delimiter, char *file)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	if (ft_strncmp(delimiter, "<", delimiter_len) == 0)
	{
		if (current->infile)
		{
			store_skipped_infiles(&current);
			free(current->infile);
		}
		current->infile = ft_strdup(file);
	}
	else if (ft_strncmp(delimiter, ">", delimiter_len) == 0
		|| ft_strncmp(delimiter, ">>", delimiter_len) == 0)
	{
		if (current->outfile)
		{
			store_skipped_outfiles(&current);
			free(current->outfile);
		}
		current->outfile = ft_strdup(file);
		if (ft_strncmp(delimiter, ">>", 2) == 0)
			current->append = 1;
	}
}
