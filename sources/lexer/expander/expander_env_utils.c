#include "lexer.h"
#include "minishell.h"

char	*find_env_value(char **env_array, char *var_name)
{
	size_t	var_name_len;
	int		i;

	var_name_len = ft_strlen(var_name);
	i = -1;
	while (env_array[++i])
	{
		if (ft_strncmp(env_array[i], var_name, var_name_len) == 0)
			return (ft_strchr(env_array[i], '=') + 1);
	}
	return (NULL);
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

char	*env_var_copy(char **token)
{
	char	*variable_name;
	char	*c_token;
	size_t	var_len;

	var_len = 0;
	(*token)++;
	c_token = *token;
	while (**token && !(**token == ' ' || **token == '"' || **token == '\''
		|| **token == '/' || **token == '$' || **token == '='))
	{
		var_len++;
		(*token)++;
	}
	variable_name = (char *)malloc((var_len + 2) * sizeof(char));
	if (!variable_name)
		exit_fail("Memmory allocation for variable_name failed.");
	strlcpy_eq(variable_name, c_token, var_len + 1);
	return (variable_name);
}

void	digit_env_var_substitute(char **token, char **result, int *i)
{
	*token += 2;
	while (**token && !(**token == ' ' || **token == '"'
		|| **token == '\''))
	{
		(*result)[*i] = *(*token)++;
		(*i)++;
	}
}
