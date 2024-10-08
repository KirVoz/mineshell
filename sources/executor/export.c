#include "lexer.h"
#include "minishell.h"

static void	update(t_minishell *minishell, const char *new_var, int env_count)
{
	minishell->env = ft_realloc_exe(minishell->env, sizeof(char *) * (env_count
				+ 2)); // +1 для новой переменной и +1 для NULL
	if (minishell->env == NULL)
		exit_fail("Failed to allocate memory for envp_var");
	minishell->env[env_count] = ft_strdup(new_var);
	if (minishell->env[env_count] == NULL)
		exit_fail("Failed to allocate memory for new_var");
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

static int	ft_check_valid_simbol(char *new_var)
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

static int	ft_check_valid_identifier(char *new_var)
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

static void declare_env_var(t_minishell *minishell, int fd)
{
	size_t	env_count;
	size_t	i;

	env_count = array_len(minishell->env);
	i = -1;
	while (++i < env_count)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(minishell->env[i], fd);
		ft_putstr_fd("\n", 1);
	}
}

static int	validation_check(t_minishell *minishell, t_cmd *cur, int fd, int *i)
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

void	execute_export(t_minishell *minishell, int fd, t_cmd *cur)
{
	char	*new_var;
	int		i;

	i = 1;
	if (validation_check(minishell, cur, fd, &i) == 1)
	{
		new_var = cur->cmd[i];
		if (ft_strchr(new_var, '=') == NULL && ft_check_valid_simbol(new_var) == 0)
			return ;
		else if (ft_check_valid_identifier(new_var) == 1)
		{
			not_valid(minishell, new_var);
			if (minishell->tmp->is_child != 0)
				exit(minishell->exit_code);
            return ;
        }
		else if (ft_check_valid_identifier(new_var) == 3)
		{
			not_valid(minishell, new_var);
			if (minishell->tmp->is_child != 0)
				exit(minishell->exit_code);
            return ;
        }
		else if (ft_check_valid_identifier(new_var) != 3)
        	add_or_update_env_var(minishell, new_var);
		minishell->exit_code = 0;
	}
	return ;
}

