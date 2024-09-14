#include "lexer.h"
#include "minishell.h"

char	**handle_heredoc(char *line)
{
	char	**tokens;
	size_t	i;
	char	*delimiter;
	char	**heredoc_tokens;
	size_t	redirections;

	i = 0;
	tokens = tokenizator(line);
	redirections = redirections_count(tokens);
	if (!redirections)
		return (tokens);
	while (redirections > 0)
	{
		delimiter = find_delimeter(tokens, &i);
		heredoc_tokens = read_heredoc_lines(delimiter);
		heredoc_tokens = merge_tokens(tokens, &heredoc_tokens, &i);
		redirections--;
	}
	free_tokens(tokens);
	return (heredoc_tokens);
}

char	**pipe_heredoc_main(char *line)
{
	char	**tokens;

	tokens = NULL;
	if (hanging_pipe_heredoc(line) == 'h')
		tokens = handle_heredoc(line);
	return (tokens);
}
