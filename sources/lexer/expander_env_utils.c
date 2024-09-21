#include "lexer.h"
#include "minishell.h"

char	*allocate_env_value(char *value)
{
	char	*env_value;

	env_value = ft_strdup(value);
	if (!env_value)
		exit_fail("Memory allocation for env_value failed.");
	return (env_value);
}

char *find_env_value(char **env_array, char *var_name)
{
    size_t var_name_len;
	int i;

    var_name_len = ft_strlen(var_name);
	i = -1;
    while (env_array[++i])
    {
        if (ft_strncmp(env_array[i], var_name, var_name_len) == 0 && env_array[i][var_name_len] == '=')
            return (ft_strchr(env_array[i], '=') + 1);
    }
    return (NULL);
}
//char	*find_env_value(t_list *env_list, char *var_name)
// {
// 	size_t	env_var_len;

// 	env_var_len = ft_strlen(env_list->content);
// 	while (env_list)
// 	{
// 		if (ft_strnstr(env_list->content, var_name, env_var_len))
// 			return (ft_strchr(env_list->content, '=') + 1);
// 		env_list = env_list->next;
// 	}
// 	return (NULL);
// }
// Изменил что бы работало не через список а через массив ! Надеюсь что правильно понял логику

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

size_t	env_value_len(t_minishell *minishell, char **token)
{
	char	*variable_name;
	char	*env_list;
	size_t	value_len;
	size_t	var_len;
	size_t	full_var_len;
	int i;

	variable_name = env_var_copy(token);
	var_len = ft_strlen(variable_name) + 1;
	value_len = 0;
	full_var_len = 0;
	i = -1;
	while (minishell->env->envp_var[++i])
	{
		env_list = minishell->env->envp_var[i];
		full_var_len = expanded_env_var_len(env_list);
		if (ft_strnstr(env_list, variable_name, full_var_len))
		{
			value_len = ft_strlen(env_list) - var_len;
			break ;
		}
	}
	free(variable_name);
	return (value_len);
}

// size_t	env_value_len(t_minishell *minishell, char **token)
// {
// 	char	*variable_name;
// 	t_list	*env_list;
// 	size_t	value_len;
// 	size_t	var_len;
// 	size_t	full_var_len;

// 	variable_name = env_var_copy(token);
// 	var_len = ft_strlen(variable_name) + 1;
// 	env_list = minishell->env->envp_var;
// 	value_len = 0;
// 	full_var_len = 0;
// 	while (env_list != NULL)
// 	{
// 		full_var_len = expanded_env_var_len(env_list->content);
// 		if (ft_strnstr(env_list->content, variable_name, full_var_len))
// 		{
// 			value_len = ft_strlen(env_list->content) - var_len;
// 			break ;
// 		}
// 		env_list = env_list->next;
// 	}
// 	free(variable_name);
// 	return (value_len);
// }
