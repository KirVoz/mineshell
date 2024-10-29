/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:16:28 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:16:29 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_var(t_minishell *minishell, const char *var_name,
		const char *new_value, int len)
{
	int		var_index;
	char	*new_entry;
	char	**new_env;

	var_index = find_string_in_array(minishell->env, var_name,
			ft_strlen(var_name));
	new_entry = ft_strjoin(var_name, new_value);
	if (!new_entry)
		return (error_free_exit(minishell, new_entry));
	if (var_index != -1)
	{
		free(minishell->env[var_index]);
		minishell->env[var_index] = new_entry;
	}
	else
	{
		new_env = ft_realloc(minishell->env, sizeof(char *) * (len),
				sizeof(char *) * (len + 2));
		if (!new_env)
			return (error_free_exit(minishell, new_entry));
		new_env[len] = new_entry;
		new_env[len + 1] = NULL;
		minishell->env = new_env;
	}
}
