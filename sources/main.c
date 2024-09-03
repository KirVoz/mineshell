#include "minishell.h"

static void init_envp(t_minishell *minishell, char **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        ft_lstadd_back(&minishell->env->envp_var, ft_lstnew(env[i]));
        i++;
    }
    ft_lstadd_back(&minishell->env->envp_var, ft_lstnew("SHLVL=1"));
}

void init_minishell(t_minishell *minishell, char **env)
{
    minishell->env = (t_env *)malloc(sizeof(t_env)); // Инициализация структуры t_env
    if (minishell->env == NULL)
    {
        perror("Failed to allocate memory for env");
        exit(EXIT_FAILURE);
    }
    minishell->env->envp_var = NULL; // Инициализация списка переменных окружения
    minishell->exit_code = 0;
    minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (minishell->cmd == NULL)
    {
        perror("Failed to allocate memory for cmd");
        exit(EXIT_FAILURE);
    }
    init_envp(minishell, env);
    
    minishell->cmd->m_av = NULL;
    minishell->cmd->m_ac = 0;
    minishell->cmd->pipes = 0;
}

int main(int ac, char **av, char **env)
{
	t_minishell minishell;
	char *line;

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
				break;
			if (line[0] != '\0')
			{
				add_history(line);
				execute(&minishell, line);
			}
			free(line);
		}
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
