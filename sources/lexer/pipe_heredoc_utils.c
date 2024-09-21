#include "lexer.h"
#include "minishell.h"

size_t	array_len(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

size_t	redirections_count(char **tokens)
{
	size_t	i;
	size_t	len;
	size_t	redirections;

	i = 0;
	len = array_len(tokens);
	redirections = 0;
	while (tokens[i])
	{
		if (i + 2 < len && *tokens[i] == '<' && *tokens[i + 1] == '<')
			redirections++;
		(i)++;
	}
	return (redirections);
}
