#include "lexer.h"
#include "minishell.h"

void	substitute_env(t_minishell *minishell, char **token, char **result,
		int *i)
{
	char	*env_value;
	char	*cp_env_value;

	env_value = get_env_value(minishell, token);
	if (!env_value)
		return ; //del should be correct return if there's no such env
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
	char	*token_cp;
	char	current_quote;
	int		in_quote;
	int		i;

	current_quote = 0;
	in_quote = 0;
	i = 0;
	token_cp = token;
// 	printf("len %zu\n", len); //del
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		exit_fail("Memmory allocation for result in expand_line failed.");
	while (*token_cp)
	{
		if ((*token_cp == '\'' || *token_cp == '\"') && !in_quote)
		{
			current_quote = set_quote(*token_cp, &in_quote);
			if (len == 2 && *(token_cp + 1) && *(token_cp + 1) == current_quote)
				result[i++] = '\n';
		}
		else if (*token_cp == current_quote && in_quote)
			in_quote = 0;
		else if (*token_cp == '$' && current_quote == '"')
		{
			substitute_env(minishell, &token_cp, &result, &i);
			continue ;
		}
		else if (*token_cp != current_quote || in_quote)
		{
			result[i] = *token_cp;
			i++;
		}
		token_cp++;
	}
	result[i] = '\0';
	free(token);
	return (result);
}

char	*expand_dollar_line(t_minishell *minishell, char *token, size_t len)
{
	char	*token_cp;
	char	*result;
	int		i;

	token_cp = token;
	i = 0;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		exit_fail("Memmory allocation for result in expand_line failed.");
	while (*token_cp)
	{
		if (*token_cp == '$')
		{
			substitute_env(minishell, &token_cp, &result, &i);
			continue ;
		}
		else
		{
			result[i] = *token_cp;
			i++;
		}
		token_cp++;
	}
	result[i] = '\0';
	free(token);
	return (result);
}

void	expander_main(t_minishell *minishell, char **tokens)
{
	char	*cp_token;
	size_t	new_line_len;

	new_line_len = 0;
	while (*tokens)
	{
		cp_token = *tokens;
		if (ft_strchr(*tokens, '"') || ft_strchr(*tokens, '\''))
		{
			new_line_len = expanded_line_len(minishell, cp_token);
// 			printf("expander_main new_line_len %zu\n", new_line_len); //del
			*tokens = expand_quoted_line(minishell, *tokens, new_line_len);
		}
		else if (dollar_special_case(tokens))
		{
			new_line_len += env_value_len(minishell, &cp_token);
// 			printf("expander_main new_line_len %zu\n", new_line_len); //del
			*tokens = expand_dollar_line(minishell, *tokens, new_line_len);
		}
		tokens++;
	}
}
