#include "lexer.h"
#include "minishell.h"

void	substitute_env(t_minishell *minishell, char **token, char **result,
		int *i)
{
	char	*env_value;
	char	*cp_env_value;

	env_value = get_env_value(minishell, token);
	if (!env_value)
		return ; // should be correct return if there's no such env
	cp_env_value = env_value;
	while (*env_value)
	{
		(*result)[*i] = *env_value;
		(*i)++;
		env_value++;
	}
	while (**token && !(**token == ' ' || **token == '"' || **token == '\''))
		(*token)++;
	free(cp_env_value);
}

char	*expand_quoted_line(t_minishell *minishell, char *token, size_t len)
{
	char	*result;
	char	current_quote;
	int		in_quote;
	int		i;

	current_quote = 0;
	in_quote = 0;
	i = 0;
	return (NULL);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		exit_fail("Memmory allocation for result in expand_line failed.");
	while (*token)
	{
		if ((*token == '\'' || *token == '\"') && !in_quote)
		{
			current_quote = set_quote(*token, &in_quote);
			if (*(token + 1) && *(token + 1) == current_quote)
				result[i] = '\0';
		}
		else if (*token == current_quote && in_quote)
			in_quote = 0;
		else if (*token == '$' && current_quote == '"')
		{
			substitute_env(minishell, &token, &result, &i);
			continue ;
		}
		else if (*token != current_quote || in_quote)
		{
			result[i] = *token;
			i++;
		}
		token++;
	}
	result[i] = '\0';
	// free(token); need to free token before reassigning, not working now
	return (result);
}

char	*expand_dollar_line(t_minishell *minishell, char *token, size_t len)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		exit_fail("Memmory allocation for result in expand_line failed.");
	while (*token)
	{
		if (*token == '$')
		{
			substitute_env(minishell, &token, &result, &i);
			continue ;
		}
		else
		{
			result[i] = *token;
			i++;
		}
		token++;
	}
	result[i] = '\0';
	// free(token); need to free token before reassigning, not working now
	return (result);
}

char	**expander_main(t_minishell *minishell, char **tokens)
{
	char	**result;
	char	*cp_token;
	size_t	new_line_len;

	result = NULL;
	cp_token = *tokens;
	new_line_len = 0;
	while (*tokens)
	{
		if (ft_strchr(*tokens, '"') || ft_strchr(*tokens, '\''))
		{
			new_line_len = expanded_line_len(minishell, *tokens) + 1;
			*tokens = expand_quoted_line(minishell, *tokens, new_line_len);
		}
		else if (ft_strchr(*tokens, '$'))
		{
			new_line_len += env_value_len(minishell, &cp_token);
			*tokens = expand_dollar_line(minishell, *tokens, new_line_len);
		}
		tokens++;
	}
	return (result);
}
