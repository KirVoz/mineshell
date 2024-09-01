#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **env)
{
	(void)env;
	minishell->env = NULL; // Initialize as needed
	minishell->exit_code = 0;
	minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (minishell->cmd == NULL)
	{
		perror("Failed to allocate memory for cmd");
		exit(EXIT_FAILURE);
	}
	// minishell->env->envp_var = env;
	minishell->cmd->m_av = NULL;
	minishell->cmd->m_ac = 0;
	minishell->cmd->pipes = 0;
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
		while (1)
		{
			init_minishell(&minishell, env);
			line = readline(PROMPT);
			if (!line)
				break ;
			if (line[0] != '\0')
			{
				add_history(line);
				execute(&minishell, line);
			}
			free(line);
		}
	}
	else
		printf("Minishell requires no arguments\n");
	return (0);
}
