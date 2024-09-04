#include "lexer.h"
#include "minishell.h"

char	**copy_tokens(char **tokens, int start, int end)
{
	int		i;
	int		j;
	char	**result;

	i = start;
	j = 0;
	result = malloc((end - start + 2) * sizeof(char *));
	if (!result)
		exit_fail("Failed to allocate memory for result in copy_tokens");
	while (i <= end)
	{
		result[j] = ft_strdup(tokens[i]);
		if (!result[j])
		{
			free_tokens(result);
			return (NULL);
		}
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

int	is_delimiter_parser(char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	if (ft_strncmp(token, "|", token_len) == 0
		|| ft_strncmp(token, "<", token_len) == 0
		|| ft_strncmp(token, ">", token_len) == 0
		|| ft_strncmp(token, "<<", token_len) == 0
		|| ft_strncmp(token, ">>", token_len) == 0)
		return (1);
	return (0);
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
