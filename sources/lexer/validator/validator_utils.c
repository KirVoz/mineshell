#include "lexer.h"
#include "minishell.h"

void	delimiter_counter(char **token, int *pipes, int *right_redirs,
		int *left_redirs)
{
	*pipes = 0;
	*right_redirs = 0;
	*left_redirs = 0;
	while (*token && ft_strchr(DELIMS, **token))
	{
		if (**token == '|')
			(*pipes)++;
		else if (**token == '>')
			(*right_redirs)++;
		else if (**token == '<')
			(*left_redirs)++;
		token++;
	}
}

int	tokens_counter(char **tokens)
{
	int	count;

	count = 0;
	while (*tokens)
	{
		if (!ft_strchr("", **tokens))
			count++;
		tokens++;
	}
	return (count);
}

char	**tokens_realloc(char ***tokens)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char **)malloc((tokens_counter(*tokens) + 1) * sizeof(char *));
	if (!res)
		exit_fail("Failed to allocate memory for tokens in tokens_realloc");
	while ((*tokens)[i])
	{
		if (*(*tokens)[i] != '\0')
		{
			res[j] = ft_strdup((*tokens)[i]);
			if (!res[j])
				exit_fail("Failed to allocate memory for token in tokens_realloc");
			free((*tokens)[i]);
			j++;
		}
		else
			free((*tokens)[i]);
		i++;
	}
	res[j] = NULL;
	free(*tokens);
	*tokens = res;
	return (res);
}
