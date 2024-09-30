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

char	*env_var_copy(char **token)
{
	char	*variable_name;
	char	*variable_tmp;
	char	*token_tmp;
	int		i;

	i = 0;
	token_tmp = *token;
	(*token)++;
	while (**token && !(**token == ' ' || **token == '"' || **token == '\''
			|| **token == '/' || **token == '$' || **token == '='))
	{
		i++;
		(*token)++;
		if (ft_isdigit(*(*token - 1)))
			break ;
	}
	variable_name = allocate_string(i, "Variable_name in env_var_copy");
	ft_strlcpy(variable_name, token_tmp + 1, i + 1);
	variable_tmp = variable_name;
	variable_name = ft_strjoin(variable_name, "=");
	if (!variable_name)
		exit_fail("Memmory allocation for variable_name failed.");
	free(variable_tmp);
	return (variable_name);
}

char	*get_env_value(t_minishell *minishell, char **token)
{
	char	*var_name;
	char	*value;
	char	*env_value;

	env_value = NULL;
	if (*(*token + 1))
	{
		var_name = env_var_copy(token);
		value = find_env_value(minishell->env, var_name);
		if (value)
			env_value = allocate_dup(value, "Env_value in get_env_value.");
		free(var_name);
	}
	else
		(*token)++;
	if (!env_value)
		env_value = allocate_dup("", "Env_value in get_env_value.");
	return (env_value);
}
