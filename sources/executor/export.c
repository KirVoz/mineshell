/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:14:08 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 19:44:52 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	update(t_minishell *minishell, const char *new_var, int env_count)
{
	int i;
	
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

static void	add_or_update_env_var(t_minishell *minishell, const char *new_var)
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

static void concatinate_env_var(t_minishell *minishell, char *cmd)
{
	char	*var_name;
	char	*add_value;
	char	*existing_value;
	char	*new_value;
	int		i;

	if	(cmd[0] == '+')
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
	i = find_string_in_array(minishell->env, var_name, ft_strlen(var_name));
	if (i == -1)
		add_or_update_env_var(minishell, cmd);
	else
	{
		existing_value = minishell->env[i] + ft_strlen(var_name) + 1;
		if (existing_value)
		{
			new_value = (char *)malloc(ft_strlen(var_name) + 1 + ft_strlen(existing_value) + ft_strlen(add_value) + 1);
			if (!new_value)
			{
				free(var_name);
				free(add_value);
				return ;
			}
			ft_strlcpy(new_value, var_name, ft_strlen(var_name) + 1);
			ft_strlcat(new_value, "=", ft_strlen(new_value) + 2);
			ft_strlcat(new_value, existing_value, ft_strlen(new_value) + ft_strlen(existing_value) + 1);
			ft_strcat(new_value, add_value);
		}
    	else
		{
			new_value = (char *)malloc(ft_strlen(var_name) + 1 + ft_strlen(add_value) + 1);
			if (!new_value)
			{
				free(var_name);
				free(add_value);
				return;
			}
			ft_strlcpy(new_value, var_name, ft_strlen(var_name) + 1);
			ft_strcat(new_value, "=");
			ft_strcat(new_value, add_value);
		}
	}
    add_or_update_env_var(minishell, new_value);
    free(new_value);
    free(var_name);
    free(add_value);
}

void execute_export(t_minishell *minishell, int fd, t_cmd *cur)
{
	int i;
	int j;
	int status; // статус выполнения для отслеживания ошибок

	if (cur->cmd[1] == NULL || cur->cmd[1][0] == '\0') // если export без аргументов или первый аргумент пустой
	{
		declare_env_var(minishell, fd);
		return;
	}
	i = 1;
	status = 0;
	while (cur->cmd[i] != NULL) // проходим по всем аргументам
	{
		j = 0;
		if (ft_strchr(cur->cmd[i], '=')) // кейс с наличием знака =
		{
			if (cur->cmd[i][j] == '=' || cur->cmd[i][j] == '+')
			{
				not_valid(minishell, cur->cmd[i], 2);
				status = 1;
			}
			// Проверка каждого символа до знака '='
			while (cur->cmd[i][j] != '=')
			{
				if (ft_check_valid_symbol(cur->cmd[i], j, 1) == 1) // если недопустимый символ
				{
					not_valid(minishell, cur->cmd[i], 1);
					status = 1;
					break;
				}
				else if (j == 0 && ft_check_valid_symbol(cur->cmd[i], j, 0) == 1) // если первый символ - цифра
				{
					not_valid(minishell, cur->cmd[i], 2);
					status = 1;
					break;
				}
				else if (ft_check_valid_symbol(cur->cmd[i], j, 1) == 2) // кейс с +=, конкатенация
				{
					concatinate_env_var(minishell, cur->cmd[i]);
					break;
				}
				j++;
			}
			// Если ошибок не было и дошли до знака '=', добавляем или обновляем переменную
			if (cur->cmd[i][j] == '=' && status == 0)
				add_or_update_env_var(minishell, cur->cmd[i]);
		}
		else // кейс без знака =
		{
			while (cur->cmd[i][j] != '\0')
			{
				if (ft_check_valid_symbol(cur->cmd[i], j, 1) == 1)  // если недопустимый символ
				{
					not_valid(minishell, cur->cmd[i], 1);
					status = 1;
					break;
				}
				else if (j == 0 && ft_check_valid_symbol(cur->cmd[i], j, 0) == 1) // если первый символ - цифра
				{
					not_valid(minishell, cur->cmd[i], 2);
					status = 1;
					break;
				}
				j++;
			}
			// Если не было ошибок, добавляем или обновляем переменную
			if (status == 0 && ft_strchr(cur->cmd[i], '='))
				add_or_update_env_var(minishell, cur->cmd[i]);
		}
		i++;
	}
	if (status == 1)
		minishell->exit_code = 1; // Устанавливаем статус ошибки, если хотя бы один аргумент невалиден
}
