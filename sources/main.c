#include "minishell.h"
#include "lexer.h"

static void	init_envp(t_minishell *minishell, char **env)
{
	int i;
	int len;

	len = 0;
	while(env[len])
		len++;
	minishell->env->envp_var = (char **)malloc(sizeof(char *) * (len + 2));
	if (minishell->env->envp_var == NULL)
		exit_fail("Failed to allocate memory for envp_var");
	i = 0;
	while(env[i] != NULL)
	{
		minishell->env->envp_var[i] = ft_strdup(env[i]);
		if (minishell->env->envp_var[i] == NULL)
			exit_fail("Failed to allocate memory for envp_var[i]");
		i++;
	}
	minishell->env->envp_var[i] = ft_strdup("SHLVL=1");
	minishell->env->envp_var[++i] = NULL;
}
void	init_tmp(t_mem *tmp)
{
	tmp->tokens = NULL;
	tmp->heredoc_tmp = NULL;
	tmp->current_heredoc = 0;
}

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env = (t_env *)malloc(sizeof(t_env));
	if (minishell->env == NULL)
		exit_fail("Failed to allocate memory for env");
	minishell->env->envp_var = NULL;
	init_envp(minishell, env);
	minishell->tmp = (t_mem *)malloc(sizeof(t_mem));
	if(!minishell->tmp)
		exit_fail("Failed to allocate memory for tmp");
	init_tmp(minishell->tmp);
	minishell->exit_code = 0;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;
	char		*line;

	(void)av;
	ft_signals();
	if (ac == 1)
	{
		init_minishell(&minishell, env); // в экзит хендлере не освобождается память для envp_var
		while (1)
		{
			line = readline(PROMPT);
			if (!line)
				break ;
			if (line[0] != '\0')
			{
				add_history(line);
            	if (!lexer_main(&minishell, line))
					continue ;
				execute(&minishell);
			}
			free(line);
		}
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
