#include "minishell.h"
#include "lexer.h"

static void	init_envp(t_minishell *minishell, char **env)
{
    int i;
    int j;
    int len;

    len = 0;
    while(env[len])
        len++;
    minishell->env->envp_var = (char **)malloc(sizeof(char *) * (len + 2));
    if (minishell->env->envp_var == NULL)
        exit_fail("Failed to allocate memory for envp_var");
    i = 0;
    j = 0;
    while(env[i] != NULL)
    {
        if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
        {
            i++;
            continue;
        }
        minishell->env->envp_var[j] = ft_strdup(env[i]);
        if (minishell->env->envp_var[j] == NULL)
            exit_fail("Failed to allocate memory for envp_var[i]");
        j++;
        i++;
    }
    minishell->env->envp_var[j] = ft_strdup("SHLVL=1");
    if (minishell->env->envp_var[j] == NULL)
        exit_fail("Failed to allocate memory for SHLVL=1");
    minishell->env->envp_var[++j] = NULL;
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
