#include "lexer.h"
#include "minishell.h"

int	pipe_redirections_mistake(t_minishell *minishell, char **tokens)
{
	int	pipes;
	int	right_redirs;
	int	left_redirs;

	while (*tokens)
	{
		delimiter_counter(tokens, &pipes, &right_redirs, &left_redirs);
		if (pipes > 1 || *tokens[0] == '|')
			return (syntax_error(minishell, "|"));
		else if (right_redirs == 3)
			return (syntax_error(minishell, ">"));
		else if (right_redirs > 3)
			return (syntax_error(minishell, ">>"));
		else if (left_redirs == 3 || left_redirs == 4)
			return (syntax_error(minishell, "<"));
		else if (left_redirs == 5)
			return (syntax_error(minishell, "<<"));
		else if (left_redirs > 5)
			return (syntax_error(minishell, "<<<"));
		tokens++;
	}
	return (1);
}

int	redirections_unification(char **tokens)
{
	int	unified;

	unified = 0;
	while (*tokens)
	{
		if (*(tokens + 1) && **tokens == '<' && **(tokens + 1) == '<')
		{
			free(*tokens);
			free(*(tokens + 1));
			*tokens = ft_strdup("<<");
			*(tokens + 1) = ft_strdup("");
			unified = 1;
		}
		else if (*(tokens + 1) && **tokens == '>' && **(tokens + 1) == '>')
		{
			free(*tokens);
			free(*(tokens + 1));
			*tokens = ft_strdup(">>");
			*(tokens + 1) = ft_strdup("");
			unified = 1;
		}
		tokens++;
	}
	return (unified);
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
				|| ft_strncmp(*tokens, ">>", token_len) == 0) && !*(tokens + 1))
			return (0);
		tokens++;
	}
	return (1);
}

int	validator_main(t_minishell *minishell, char ***tokens)
{
	if (!pipe_redirections_mistake(minishell, *tokens))
		return (0);
	redirections_check(tokens);
	if (!hanging_redirections(*tokens))
		return (syntax_error(minishell, "newline"));
	
	return (1);
}
