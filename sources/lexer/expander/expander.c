#include "lexer.h"
#include "minishell.h"

void	substitute_env(t_minishell *minishell, char **token, char **result,
		int *i)
{
	char	*env_value;
	char	*cp_env_value;

	if (*(*token + 1) && ft_isdigit(*(*token + 1)))
		return (digit_env_var_substitute(token, result, i));
	// (*token)++;
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
	// while (**token && !(**token == ' ' || **token == '"' || **token == '\''))
	// 	(*token)++;
	// while (**token && !(**token == ' ' || **token == '"' || **token == '\''))
	// {
	// 	(*result)[*i] = *(*token)++;
	// 	(*i)++;
	// }
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
	// printf("len %zu\n", len); //del
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
		else if (*token_cp == '$' && current_quote == '"'
			&& !(*(token_cp + 1) == '"' || *(token_cp + 1) == '\''))
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
		if (*token_cp == '$' && *(token_cp + 1))
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

size_t	count_to_dollar(char **line)
{
	size_t	len;

	len = 0;
	while (**line && **line != '$')
	{
		len++;
		(*line)++;
	}
	return (len);
}

size_t	exit_len(char *token, char *exit_code)
{
	size_t	len;

	len = 0;
	while (*token)
	{
		if (*token == '$' && *(token + 1) && *(token + 1) == '?')
		{
			len += ft_strlen(exit_code);
			token++;
		}
		else if (*token != '"')
			len++;
		token++;
	}
	return (len);
}

void	write_exit_code(char **result, char *exit_code, int *i)
{
	while (*exit_code)
	{
		(*result)[*i] = *exit_code;
		(*i)++;
		exit_code++;
	}
}

char	*allocate_result(size_t len)
{
	char	*result;

	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		exit_fail("Memmory allocation for result in expand_question_mark failed.");
	return (result);
}

char	*expand_question_mark(t_minishell *minishell, char *token)
{
	char	*result;
	char	*token_cp;
	char	*exit_code;
	int		i;

	i = 0;
	token_cp = token;
	exit_code = ft_itoa(minishell->exit_code);
	result = allocate_result(exit_len(token, exit_code));
	while (*token)
	{
		if (*token == '$' && *(token + 1) && *(token + 1) == '?')
		{
			write_exit_code(&result, exit_code, &i);
			token += 2;
		}
		else if (*token == '"')
			token++;
		else
			result[i++] = *(token++);
	}
	result[i] = '\0';
	free(token_cp);
	return (result);
}

void	expander_main(t_minishell *minishell, char **tokens)
{
	char	*token_cp;
	size_t	new_line_len;

	new_line_len = 0;
	while (*tokens)
	{
		token_cp = *tokens;
		if (ft_strnstr(*tokens, "$?", ft_strlen(*tokens))
			&& !ft_strchr(*tokens, '\''))
			*tokens = expand_question_mark(minishell, *tokens);
		else if (ft_strchr(*tokens, '"') || ft_strchr(*tokens, '\''))
		{
			new_line_len = expanded_line_len(minishell, token_cp);
			*tokens = expand_quoted_line(minishell, *tokens, new_line_len);
		}
		else if (ft_strchr(*tokens, '$') && ft_strlen(*tokens) > 1)
		{
			if (**tokens != '$')
				new_line_len += count_to_dollar(&token_cp);
			new_line_len += env_value_len(minishell, &token_cp);
			*tokens = expand_dollar_line(minishell, *tokens, new_line_len);
		}
		tokens++;
	}
	token_cp = NULL;
}
