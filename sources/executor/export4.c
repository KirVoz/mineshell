/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:38 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:47:28 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static char	*allocate_and_concat(const char *var_name,
	const char *existing_value, const char *add_value)
{
	char	*new_value;
	size_t	new_size;
	size_t	existing_value_len;

	existing_value_len = 0;
	if (existing_value)
		existing_value_len = ft_strlen(existing_value);
	new_size = ft_strlen(var_name) + 1 + existing_value_len
		+ ft_strlen(add_value) + 1;
	new_value = (char *)malloc(new_size);
	if (!new_value)
		return (NULL);
	ft_strlcpy(new_value, var_name, ft_strlen(var_name) + 1);
	ft_strlcat(new_value, "=", ft_strlen(new_value) + 2);
	if (existing_value)
		ft_strlcat(new_value, existing_value, ft_strlen(new_value)
			+ existing_value_len + 1);
	ft_strlcat(new_value, add_value, new_size);
	return (new_value);
}

static void	free_free_hate_norm(char *var_name, char *add_value)
{
	free(var_name);
	free(add_value);
}

static void	handle_existing_value(t_minishell *minishell, char *var_name,
	char *add_value, int i)
{
	char	*existing_value;
	char	*new_value;

	existing_value = minishell->env[i] + ft_strlen(var_name) + 1;
	if (existing_value)
	{
		new_value = allocate_and_concat(var_name, existing_value, add_value);
		if (!new_value)
		{
			free_free_hate_norm(var_name, add_value);
			return ;
		}
	}
	else
	{
		new_value = allocate_and_concat(var_name, NULL, add_value);
		if (!new_value)
		{
			free_free_hate_norm(var_name, add_value);
			return ;
		}
	}
	add_or_update_env_var(minishell, new_value);
	free(new_value);
}

static void	handle_new_value(t_minishell *minishell, char *cmd, char *var_name,
	char *add_value)
{
	int	i;

	i = find_string_in_array(minishell->env, var_name, ft_strlen(var_name));
	if (i == -1)
		add_or_update_env_var(minishell, cmd);
	else
		handle_existing_value(minishell, var_name, add_value, i);
}

void	concatinate_env_var(t_minishell *minishell, char *cmd)
{
	char	*var_name;
	char	*add_value;

	if (cmd[0] == '+')
		return ;
	var_name = find_var_name(cmd);
	if (!var_name)
		return ;
	add_value = ft_strdup(ft_strchr(cmd, '=') + 1);
	if (!add_value)
	{
		free(var_name);
		return ;
	}
	handle_new_value(minishell, cmd, var_name, add_value);
	free(var_name);
	free(add_value);
}
