#include "minishell.h"
#include "lexer.h"

static void	init_envp(t_minishell *minishell, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			i++;
		ft_lstadd_back(&minishell->env->envp_var, ft_lstnew(env[i]));
		i++;
	}
	ft_lstadd_back(&minishell->env->envp_var, ft_lstnew("SHLVL=1"));
}

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env = (t_env *)malloc(sizeof(t_env));
	// Инициализация структуры t_env
	if (minishell->env == NULL)
		exit_fail("Failed to allocate memory for env");
	minishell->env->envp_var = NULL;
	// Инициализация списка переменных окружения
	minishell->exit_code = 0;
	minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (minishell->cmd == NULL)
		exit_fail("Failed to allocate memory for cmd");
	init_envp(minishell, env);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;
	char		*line;

	(void)av;
	(void)env;
	ft_signals();
	if (ac == 1)
	{
		init_minishell(&minishell, env);
		while (1)
		{
			line = readline(PROMPT);
			if (!line)
				break ;
			if (line[0] != '\0')
			{
				add_history(line);
            	lexer_main(&minishell, line);
				execute(&minishell, env);
			}
			free(line);
		}
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
