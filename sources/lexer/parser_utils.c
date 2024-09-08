#include "lexer.h"
#include "minishell.h"

int	if_pipe(char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	if (ft_strncmp(token, "|", token_len) == 0)
		return (1);
	return (0);
}

int	is_redirection(char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	if (ft_strncmp(token, "<", token_len) == 0
		|| ft_strncmp(token, ">", token_len) == 0
		|| ft_strncmp(token, "<<", token_len) == 0
		|| ft_strncmp(token, ">>", token_len) == 0)
		return (1);
	return (0);
}

void	handle_redirections(t_cmd *current, char *delimiter, char *file)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	if (ft_strncmp(delimiter, "<", delimiter_len) == 0 || ft_strncmp(delimiter,
			"<<", delimiter_len) == 0)
	{
		free(current->infile);
		current->infile = ft_strdup(file);
	}
	else if (ft_strncmp(delimiter, ">", delimiter_len) == 0
		|| ft_strncmp(delimiter, ">>", delimiter_len) == 0)
	{
		free(current->outfile);
		current->outfile = ft_strdup(file);
	}
}
