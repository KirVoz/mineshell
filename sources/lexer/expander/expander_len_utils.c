#include "lexer.h"
#include "minishell.h"

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
		else if (*token == '$' && current_quote == '"'
			&& !(*(token + 1) == '"' || *(token + 1) == '\''))
		{
			len += env_value_len(minishell, &token);
			// printf("expanded_line_len %zu\n", len); //del
			continue ;
		}
		else if (*token != current_quote || in_quote)
			len++;
		token++;
	}
	return (len);
}

size_t	env_value_len(t_minishell *minishell, char **token)
{
	char	*variable_name;
	char	*env_list;
	size_t	value_len;
	size_t	var_len;
	int		i;

	if (*(*token + 1) && ft_isdigit(*(*token + 1)))
		return (digit_env_var_len(token));
	variable_name = env_var_copy(token);
	var_len = ft_strlen(variable_name);
	value_len = 0;
	i = -1;
	while (minishell->env->envp_var[++i])
	{
		env_list = minishell->env->envp_var[i];
		if (ft_strnstr(env_list, variable_name, var_len))
		{
			value_len = ft_strlen(env_list) - var_len;
			if (*token)
				value_len += additional_len(*token);
			break ;
		}
	}
	free(variable_name);
	return (value_len);
}

size_t	digit_env_var_len(char **token)
{
	size_t	len;

	len = 0;
	*token += 2;
	while (**token && !(**token == ' ' || **token == '"' || **token == '\''
		|| **token == '/' || **token == '$' || **token == '='))
	{
		len++;
		(*token)++;
	}
	return (len);
}

size_t	additional_len(char *token)
{
	size_t	len;

	len = 0;
	while (*token && !ft_strchr(" \n\"\'", *token))
	{
		len++;
		token++;
	}
	return (len);
}
