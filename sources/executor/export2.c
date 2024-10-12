/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:38 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:47:28 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	ft_check_valid_simbol(char *new_var)
{
	int	i;

	i = 0;
	if (new_var[i] >= '0' && new_var[i] <= '9' && new_var[i] != '=')
		return (1);
	while (new_var[i] != '=')
	{
		if (new_var[i] == '@' || new_var[i] == '*' || new_var[i] == '#'
			|| new_var[i] == '?' || new_var[i] == '-' || new_var[i] == '$'
			|| new_var[i] == '!' || new_var[i] == '+' || new_var[i] == '~')
			return (1);
		if (new_var[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

int	ft_check_valid_identifier(char *new_var)
{
	int	i;

	i = 0;
	if (new_var[i] >= '0' && new_var[i] <= '9' && new_var[i] != '=')
		return (1);
	if (!ft_strchr(new_var, '='))
		return (3);
	while (new_var[i] == '=' || new_var[i] == '\0')
	{
		i++;
		return (1);
	}
	while (new_var[i] != '=')
	{
		if (new_var[i] == '@' || new_var[i] == '*' || new_var[i] == '#'
			|| new_var[i] == '?' || new_var[i] == '-' || new_var[i] == '$'
			|| new_var[i] == '!' || new_var[i] == '+' || new_var[i] == '~')
			return (1);
		if (new_var[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

int	validation_check(t_minishell *minishell, t_cmd *cur, int fd, int *i)
{
	if (cur->cmd[*i] == NULL)
	{
		declare_env_var(minishell, fd);
		return (0);
	}
	else
	{
		while (cur->cmd[*i][0] == '\0')
		{
			if (cur->cmd[*i + 1] == NULL)
			{
				declare_env_var(minishell, fd);
				return (0);
			}
			(*i)++;
		}
		return (1);
	}
}

char	*construct_declare(char *env_var)
{
	char	*new_var;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_var = allocate_string(ft_strlen(env_var) + 2, "New_var");
	while (env_var[i] != '=')
		new_var[j++] = env_var[i++];
	new_var[j++] = env_var[i++];
	new_var[j++] = '"';
	while (env_var[i])
		new_var[j++] = env_var[i++];
	new_var[j++] = '"';
	new_var[j] = '\0';
	return (new_var);
}
