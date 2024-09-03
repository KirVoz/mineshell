#include "lexer.h"
#include "minishell.h"

char	*env_var_copy(char **token)
{
	char	*variable_name;
	char	*c_token;
	size_t	var_len;

	var_len = 0;
	(*token)++;
	c_token = *token;
	while (**token && !(**token == ' ' || **token == '"' || **token == '\''))
	{
		var_len++;
		(*token)++;
	}
	variable_name = (char *)malloc((var_len + 1) * sizeof(char));
	if (!variable_name)
		exit_fail("Memmory allocation for variable_name failed.");
	ft_strlcpy(variable_name, c_token, var_len + 1);
	return (variable_name);
}

size_t	expanded_env_var_len(char *line)
{
	int	len;

	len = 0;
	while (*line && *line != '\n')
	{
		len++;
		line++;
	}
	return (len);
}

size_t	env_value_len(t_minishell *minishell, char **token)
{
	char	*variable_name;
	t_list	*env_list;
	size_t	value_len;
	size_t	var_len;
	size_t	full_var_len;

	variable_name = env_var_copy(token);
	var_len = ft_strlen(variable_name) + 1;
	env_list = minishell->env->envp_var;
	value_len = 0;
	full_var_len = 0;
	while (env_list != NULL)
	{
		full_var_len = expanded_env_var_len(env_list->content);
		if (ft_strnstr(env_list->content, variable_name, full_var_len))
		{
			value_len = ft_strlen(env_list->content) - var_len;
			break ;
		}
		env_list = env_list->next;
	}
	free(variable_name);
	return (value_len);
}

char	set_quote(char c, int *in_quote)
{
	*in_quote = 1;
	return (c);
}

size_t	expanded_line_len(t_minishell *minishell, char *token)
{
	char	current_quote;
	size_t	len;
	int		in_quote;

	current_quote = 0;
	len = 0;
	in_quote = 0;
	while (*token)
	{
		if ((*token == '\'' || *token == '\"') && !in_quote)
			current_quote = set_quote(*token, &in_quote);
		else if (*token == current_quote && in_quote)
			in_quote = 0;
		else if (*token == '$' && current_quote == '"')
		{
			len += env_value_len(minishell, &token);
			continue ;
		}
		else if (*token != current_quote || in_quote)
			len++;
		token++;
	}
	return (len);
}

char	*find_env_value(t_list *env_list, char *var_name)
{
	size_t	env_var_len;

	env_var_len = ft_strlen(env_list->content);
	while (env_list)
	{
		if (ft_strnstr(env_list->content, var_name, env_var_len))
			return (ft_strchr(env_list->content, '=') + 1);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*allocate_env_value(char *value)
{
	char	*env_value;

	env_value = ft_strdup(value);
	if (!env_value)
		exit_fail("Memory allocation for env_value failed.");
	return (env_value);
}

char	*get_env_value(t_minishell *minishell, char **token)
{
	char	*var_name;
	char	*value;
	char	*env_value;

	var_name = env_var_copy(token);
	value = find_env_value(minishell->env->envp_var, var_name);
	if (value)
		env_value = allocate_env_value(value);
	else
		env_value = NULL;
	free(var_name);
	return (env_value);
}

void	substitute_env(t_minishell *minishell, char **token, char **result,
		int *i)
{
	char	*env_value;
	char	*cp_env_value;

	env_value = get_env_value(minishell, token);
	if (!env_value)
		return ; // correct return if there's no such env
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
char	*expand_line(t_minishell *minishell, char *token, size_t len)
{
	char	*result;
	char	current_quote;
	int		in_quote;
	int		i;

	current_quote = 0;
	in_quote = 0;
	i = 0;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		exit_fail("Memmory allocation for result in expand_line failed.");
	while (*token)
	{
		if ((*token == '\'' || *token == '\"') && !in_quote)
			current_quote = set_quote(*token, &in_quote);
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

char	*expand_line_dollar(t_minishell *minishell, char *token, size_t len)
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

char	**expander(t_minishell *minishell, char **tokens)
{
	char **result;
	char *cp_token;
	size_t new_line_len;

	result = NULL;
	cp_token = *tokens;
	new_line_len = 0;
	while (*tokens)
	{
		if (ft_strchr(*tokens, '"') || ft_strchr(*tokens, '\''))
		{
			new_line_len = expanded_line_len(minishell, *tokens) + 1;
			*tokens = expand_line(minishell, *tokens, new_line_len);
		}
		else if (ft_strchr(*tokens, '$'))
		{
			new_line_len += env_value_len(minishell, &cp_token);
			*tokens = expand_line_dollar(minishell, *tokens, new_line_len);
		}
		tokens++;
	}
	return (result);
}