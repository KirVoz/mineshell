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

char	**tokens_realloc(char **tokens)
{
	char	**res;
	char	**cp_res;
	char	**cp_tokens;

	cp_tokens = tokens;
	res = (char **)malloc((tokens_counter(tokens) + 1) * sizeof(char *));
	if (!res)
		exit_fail("Failed to allocate memory for tokens in tokens_realloc");
	cp_res = res;
	while (*cp_tokens)
	{
		if (!ft_strchr("", **cp_tokens))
		{
			*cp_res = ft_strdup(*cp_tokens);
			if (!cp_res)
				exit_fail("Failed to allocate memory for token in tokens_realloc");
			free(*cp_tokens);
			cp_res++;
		}
		cp_tokens++;
	}
	*cp_res = NULL;
	cp_res = NULL;
	free(tokens);
	return (res);
}

int	redirections_check(char ***tokens)
{
	if (redirections_unification(*tokens))
		*tokens = tokens_realloc(*tokens);
	return (0);
}
