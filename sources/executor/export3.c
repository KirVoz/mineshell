/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:38 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:47:28 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < n)
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*find_var_name(char *cmd)
{
	char	*plus;
	size_t	len;
	char	*res;

	plus = ft_strchr(cmd, '+');
	if (!plus)
		return (NULL);
	len = plus - cmd;
	res = ft_strndup(cmd, len);
	return (res);
}

void	*ft_strcat(char *dst, const char *src)
{
	char	*dst_start;

	dst_start = dst;
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_start);
}

static void	update(t_minishell *minishell, const char *new_var, int env_count)
{
	int	i;

	minishell->env = ft_realloc(minishell->env, sizeof(char *) * (env_count),
			sizeof(char *) * (env_count + 2));
	if (minishell->env == NULL)
		exit_fail("Failed to allocate memory for envp_var");
	minishell->env[env_count] = ft_strdup(new_var);
	if (minishell->env[env_count] == NULL)
	{
		i = -1;
		while (++i < env_count)
			free(minishell->env[i]);
		free(minishell->env);
		exit_fail("Failed to allocate memory for new_var");
	}
	else
		minishell->env[env_count + 1] = NULL;
}

void	add_or_update_env_var(t_minishell *minishell, const char *new_var)
{
	size_t	i;
	char	*existing_var;
	size_t	env_count;
	size_t	var_name_len;

	env_count = array_len(minishell->env);
	var_name_len = ft_strchr(new_var, '=') - new_var;
	i = -1;
	while (++i < env_count)
	{
		existing_var = minishell->env[i];
		if (ft_strncmp(existing_var, new_var, var_name_len) == 0
			&& (existing_var[var_name_len] == '='
				|| existing_var[var_name_len] == '\0'))
		{
			free(minishell->env[i]);
			minishell->env[i] = ft_strdup(new_var);
			if (minishell->env[i] == NULL)
				exit_fail("Failed to allocate memory for envp_var element");
			return ;
		}
	}
	update(minishell, new_var, env_count);
	minishell->exit_code = 0;
}
