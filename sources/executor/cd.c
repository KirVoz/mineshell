#include "minishell.h"

static void	update_env_var(t_minishell *minishell, const char *var_name,
		const char *new_value)
{
	int	var_index;

	var_index = find_string_in_array(minishell->env, var_name,
			ft_strlen(var_name));
	if (var_index != -1)
	{
		free(minishell->env[var_index]);
		minishell->env[var_index] = ft_strjoin(var_name, new_value);
	}
}

static void	update_pwd_vars(t_minishell *minishell, const char *old_pwd,
		const char *new_path)
{
	update_env_var(minishell, "OLDPWD=", old_pwd);
	update_env_var(minishell, "PWD=", new_path);
	// printf("%s\n", new_path); //del
}

static void	change_directory(t_minishell *minishell, const char *new_path)
{
	char	cwd[1024];
	char	*old_pwd;

	old_pwd = ft_strdup(minishell->env[find_string_in_array(minishell->env,
			"PWD=", 4)] + 4);
	if (chdir(new_path) || getcwd(cwd, sizeof(cwd)) == NULL)
	{
  		if (minishell->tmp->is_child != 0)
   			free(old_pwd);
  		deleted_dir(minishell);
	}
	else
	{
		update_pwd_vars(minishell, old_pwd, cwd);
		minishell->exit_code = 0;
	}
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
	else
		change_directory(minishell, cur->cmd[1]);
}
