#include "lexer.h"
#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_data;
	char	*src_data;

	if (!dst && !src)
		return (dst);
	i = 0;
	dst_data = (char *)dst;
	src_data = (char *)src;
	while (i < n)
	{
		dst_data[i] = src_data[i];
		i++;
	}
	return (dst);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size;

	if (old_size < new_size)
		size = old_size;
	else
		size = new_size;
	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	ft_bzero(new_ptr, new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

char	**array_init(void)
{
	char	**empty_array;

	empty_array = (char **)malloc(2 * sizeof(char *));
	if (!empty_array)
		exit_fail("Failed to allocate memory for empty command");
	empty_array[0] = ft_strdup("");
	empty_array[1] = NULL;
	return (empty_array);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	if (cmd->cmd != NULL)
	{
		while (cmd->cmd[i] != NULL)
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}   
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->skipped_in);
	free(cmd->skipped_out);
	free_cmd(cmd->next);
	free(cmd);
}

void	free_heredoc_tmp(char ***heredoc_tmp)
{
	int	i;

	i = 0;
	while (heredoc_tmp[i])
	{
		free_tokens(heredoc_tmp[i]);
		i++;
	}
	free(heredoc_tmp);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell == NULL)
		return ;
	minishell->current_heredoc = 0;
	if (minishell->heredoc_tmp)
		free_heredoc_tmp(minishell->heredoc_tmp);
	free_cmd(minishell->cmd);
}
