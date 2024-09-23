#include "minishell.h"
#include "lexer.h"

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	(void)av;
	ft_signals();
	if (ac == 1)
	{
		init_minishell(&minishell, env); // в экзит хендлере не освобождается память для envp_var
		while (1)
		{
			minishell.tmp->line = readline(PROMPT);
			if (!minishell.tmp->line)
				break ;
			if (minishell.tmp->line[0] != '\0')
			{
				add_history(minishell.tmp->line);
            	if (!lexer_main(&minishell, minishell.tmp->line))
					continue ;
				execute(&minishell);
			}
		}
		exit_free(&minishell, minishell.exit_code);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
