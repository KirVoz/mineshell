#include "minishell.h"
#include "lexer.h"

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
		exit_free(&minishell, minishell.exit_code);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
