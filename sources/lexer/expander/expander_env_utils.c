/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:24:38 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:24:39 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		env_value = allocate_dup(value, "Env_value in get_env_value.");
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

void	substitute_env(t_minishell *minishell, char **token, char **result,
		int *i)
{
	char	*env_value;
	char	*cp_env_value;

	if (*(*token + 1) && ft_isdigit(*(*token + 1)))
		return (digit_env_var_substitute(token, result, i));
	env_value = get_env_value(minishell, token);
	if (!env_value)
		return ;
	cp_env_value = env_value;
	while (*env_value)
	{
		(*result)[*i] = *env_value;
		(*i)++;
		env_value++;
	}
	free(cp_env_value);
}
