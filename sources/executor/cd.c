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

static void	update_pwd_vars(t_minishell *minishell, const char *old_pwd,
		const char *new_path)
{
	int	len;

	len = ft_array_len(minishell->env);
	update_env_var(minishell, "OLDPWD=", old_pwd, len);
	update_env_var(minishell, "PWD=", new_path, len);
}

static void	change_directory(t_minishell *minishell, const char *new_path)
{
	char	cwd[1024];
	char	*old_pwd;
	int		i;

	i = find_string_in_array(minishell->env, "PWD=", 4);
	if (i == -1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			minishell->exit_code = 1;
			return;
		}
		old_pwd = ft_strdup(cwd);
		update_env_var(minishell, "PWD=", cwd, ft_array_len(minishell->env));
	}
	else
		old_pwd = ft_strdup(minishell->env[i] + 4);
	if (chdir(new_path) || getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (minishell->tmp->is_child != 0)
		{	
			free(old_pwd);
			old_pwd = NULL;
		}
		deleted_dir(minishell);
	}
	else
	{
		update_pwd_vars(minishell, old_pwd, cwd);
		minishell->exit_code = 0;
	}
	if (old_pwd != NULL)
		free(old_pwd);
}

static void	change_to_home_directory(t_minishell *minishell)
{
	int	home_index;

	home_index = find_string_in_array(minishell->env, "HOME=", 5);
	if (home_index == -1)
	{
		printf("HOME environment variable not found\n");
		minishell->exit_code = 1;
		return ;
	}
	change_directory(minishell, minishell->env[home_index] + 5);
}

void	execute_cd(t_minishell *minishell, int fd, t_cmd *cur)
{
	(void)fd;
	if (cur->cmd[1] == NULL)
		change_to_home_directory(minishell);
	else if (cur->cmd[1][0] == '-' && cur->cmd[1][1] == '\0')
	{
		if (find_string_in_array(minishell->env, "OLDPWD=", 7) == -1)
		{
			printf("OLDPWD not set\n");
			minishell->exit_code = 1;
			return ;
		}
		else
			change_directory(minishell, minishell->env[find_string_in_array(
				minishell->env, "OLDPWD=", 7)] + 7);
	}
	else
		change_directory(minishell, cur->cmd[1]);
}
