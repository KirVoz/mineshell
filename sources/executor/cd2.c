/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:57:22 by aaleksee          #+#    #+#             */
/*   Updated: 2024/10/30 00:57:24 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd_vars(t_minishell *minishell, const char *old_pwd,
		const char *new_path)
{
	int	len;

	len = ft_array_len(minishell->env);
	update_env_var(minishell, "OLDPWD=", old_pwd, len);
	update_env_var(minishell, "PWD=", new_path, len);
}

static void	setup_old_pwd(t_minishell *minishell, char **old_pwd)
{
	char	cwd[1024];
	int		i;

	i = find_string_in_array(minishell->env, "PWD=", 4);
	if (i == -1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			printf("!getcwd\n");
			no_file(minishell, "PWD");
			*old_pwd = NULL;
			return ;
		}
		*old_pwd = ft_strdup(cwd);
		update_env_var(minishell, "PWD=", cwd, ft_array_len(minishell->env));
	}
	else
		*old_pwd = ft_strdup(minishell->env[i] + 4);
}

static void	change_directory(t_minishell *minishell, char *new_path)
{
	char	cwd[1024];
	char	*old_pwd;

	setup_old_pwd(minishell, &old_pwd);
	if (old_pwd == NULL)
		return ;
	if (chdir(new_path) != 0)
		no_file(minishell, new_path);
	else if (getcwd(cwd, sizeof(cwd)) == NULL)
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
			change_directory(minishell, minishell->env
			[find_string_in_array(minishell->env, "OLDPWD=", 7)] + 7);
	}
	else
		change_directory(minishell, cur->cmd[1]);
}
