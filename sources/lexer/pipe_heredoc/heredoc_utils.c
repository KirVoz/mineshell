#include "lexer.h"
#include "minishell.h"

char	*find_delimiter(char **tokens, size_t *i)
{
	char	*delimiter;
	size_t	len;

	delimiter = NULL;
	len = array_len(tokens);
	while (tokens[*i])
	{
		if (*i + 2 < len && *tokens[*i] == '<' && *tokens[*i + 1] == '<')
		{
			*i += 2;
			delimiter = ft_strdup(tokens[*i]);
			if (!delimiter)
				exit_fail("Failed to allocate memory for delimiter");
			break ;
		}
		(*i)++;
	}
	return (delimiter);
}

char	**read_heredoc_lines(char *delimiter)
{
	char	**heredoc_tokens;
	size_t	size;
	size_t	capacity;
	char	*new_line;

	capacity = 2;
	heredoc_tokens = (char **)malloc(capacity * sizeof(char *));
	if (!heredoc_tokens)
		exit_fail("Failed to allocate memory for heredoc tokens");
	*heredoc_tokens = NULL;
	size = 0;
	while (1)
	{
		new_line = readline(PROMPT_HEREDOC);
		if (ft_strlen(new_line) != 0 && ft_strncmp(new_line, delimiter, strlen(new_line)) == 0)
		{
			free(new_line);
			break ;
		}
		add_line_to_heredoc(&heredoc_tokens, &size, &capacity, new_line);
		free(new_line);
	}
	heredoc_tokens[size] = NULL;
	heredoc_tokens = (char **)ft_realloc(heredoc_tokens, (size + 1)
			* sizeof(char *), (size + 1) * sizeof(char *));
	if (!heredoc_tokens)
		exit_fail("Failed to reallocate memory for heredoc tokens");
	free(delimiter);
	return (heredoc_tokens);
}

void	add_line_to_heredoc(char ***heredoc_tokens, size_t *size,
		size_t *capacity, char *line)
{
	size_t	old_capacity;

	old_capacity = *capacity;
	if (*size == *capacity - 1)
	{
		(*capacity) *= 2;
		*heredoc_tokens = (char **)ft_realloc(*heredoc_tokens, old_capacity
				* sizeof(char *), *capacity * sizeof(char *));
		if (!*heredoc_tokens)
			exit_fail("Failed to reallocate memory for heredoc tokens");
	}
	(*heredoc_tokens)[(*size)++] = ft_strdup(line);
	if (!(*heredoc_tokens)[*size - 1])
		exit_fail("Failed to allocate memory for heredoc tokens");
}
