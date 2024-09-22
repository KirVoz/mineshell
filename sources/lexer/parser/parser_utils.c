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

void	store_skipped_infiles(t_cmd **current)
{
	ft_lstadd_back(&(*current)->skipped_in,
		ft_lstnew(ft_strdup((*current)->infile)));
	free((*current)->infile);
}

void	store_skipped_outfiles(t_cmd **current)
{
	ft_lstadd_back(&(*current)->skipped_out,
		ft_lstnew(ft_strdup((*current)->outfile)));
	free((*current)->outfile);
}

void	handle_redirections(t_cmd *current, char *delimiter, char *file)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	if (ft_strncmp(delimiter, "<", delimiter_len) == 0)
	{
		if (current->infile)
			store_skipped_infiles(&current);
		current->infile = ft_strdup(file);
	}
	else if (ft_strncmp(delimiter, ">", delimiter_len) == 0
		|| ft_strncmp(delimiter, ">>", delimiter_len) == 0)
	{
		if (current->outfile)
			store_skipped_outfiles(&current);
		current->outfile = ft_strdup(file);
		if (ft_strncmp(delimiter, ">>", 2) == 0)
			current->append = 1;
	}
}
