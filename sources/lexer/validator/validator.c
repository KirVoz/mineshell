#include "lexer.h"
#include "minishell.h"

int	checek_two_tokens(char *token, char *next_token)
{
	if (ft_strncmp(token, ">", 1) == 0 && ft_strncmp(next_token, ">", 1) == 0)
		return (1);
	if (ft_strncmp(token, "<", 1) == 0 && ft_strncmp(next_token, "<", 1) == 0)
		return (1);
	return (0);
}

int	redirections_unification_required(char **tokens)
{
	int		required;
	char	a;
	int		i;

	required = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i + 1] && checek_two_tokens(tokens[i], tokens[i + 1]))
		{
			a = tokens[i][0];
			free(tokens[i]);
			if (a == '>')
				tokens[i] = ft_strdup(">>");
			else
				tokens[i] = ft_strdup("<<");
			free(tokens[i + 1]);
			tokens[i + 1] = ft_strdup("");
			required = 1;
		}
		i++;
	}
	return (required);
}

int	hanging_redirections(char **tokens)
{
	size_t	token_len;

	while (*tokens)
	{
		token_len = ft_strlen(*tokens);
		if ((ft_strncmp(*tokens, "<", token_len) == 0
				|| ft_strncmp(*tokens, ">", token_len) == 0
				|| ft_strncmp(*tokens, "<<", token_len) == 0
				|| ft_strncmp(*tokens, ">>", token_len) == 0) && !*(tokens + 1)
			&& token_len != 0)
			return (0);
		tokens++;
	}
	return (1);
}

int	is_valid_token(char *token)
{
	char	*valid_t[6] = VALID_TOKENS;
	int		i;

	i = 0;
	while (valid_t[i])
	{
		if (ft_strncmp(token, valid_t[i], ft_strlen(valid_t[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	pipe_redirections_mistake(t_minishell *minishell, char **tokens)
{
	if (**tokens == '|')
		return (syntax_error(minishell, "|"));
	while (*tokens)
	{
		if (is_valid_token(*tokens) && *(tokens + 1)
			&& is_valid_token(*(tokens + 1)))
		return (syntax_error(minishell, *(tokens + 1)));
		tokens++;
	}
	return (1);
}

int	validator_main(t_minishell *minishell, char ***tokens)
{
	if (redirections_unification_required(*tokens))
		*tokens = tokens_realloc(tokens);
	if (!pipe_redirections_mistake(minishell, *tokens))
		return (0);
	if (!hanging_redirections(*tokens))
		return (syntax_error(minishell, "newline"));
	return (1);
}
