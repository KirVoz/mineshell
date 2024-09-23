#include "lexer.h"
#include "minishell.h"

int	incorrect_delimiter(char *delimiter)
{
	char	*tokens[6] = VALID_TOKENS;
	int		i = 0;
	
	while (tokens[i])
	{
		if (ft_strncmp(delimiter, tokens[i], ft_strlen(tokens[i])) == 0)
		{
			free (delimiter);
			return (0);
		}
		i++;
	}
	return (1);
}

void	add_heredocs(t_minishell *minishell, char **tokens, size_t redirections)
{
	char	***heredoc_tmp;
	size_t	i;
	size_t	heredoc_index;
	char	*delimiter;
	char	**heredoc_tokens;

	i = 0;
	heredoc_index = 0;
	heredoc_tmp = (char ***)malloc((redirections + 1) * sizeof(char **));
	if (!heredoc_tmp)
		exit_fail("Failed to allocate memory for heredoc_tmp");
	minishell->tmp->heredoc_tmp = heredoc_tmp;
	while (heredoc_index < redirections)
	{
		delimiter = find_delimiter(tokens, &i);
		if (!incorrect_delimiter(delimiter))
			return ;
		heredoc_tokens = read_heredoc_lines(delimiter);
		expander_main(minishell, heredoc_tokens);
		minishell->tmp->heredoc_tmp[heredoc_index] = heredoc_tokens;
		heredoc_index++;
	}
	minishell->tmp->heredoc_tmp[redirections] = NULL;
}

char	**handle_heredoc(t_minishell *minishell, char **tokens)
{
	size_t	redirections;

	redirections = redirections_count(tokens);
	if (!redirections)
		return (tokens);
	add_heredocs(minishell, tokens, redirections);
	return (tokens);
}

char	**pipe_heredoc_main(t_minishell *minishell, char *line)
{
	char	**tokens;

	tokens = tokenizator(line);
	if (hanging_pipe_heredoc(line) == 'h')
		tokens = handle_heredoc(minishell, tokens);
	return (tokens);
}
