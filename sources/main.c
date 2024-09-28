#include "minishell.h"
#include "lexer.h"

static int	check_line(t_minishell minishell)
{
	if (minishell.tmp->line[0] == '\0')
	{
		free(minishell.tmp->line);
		return (1);
	}
	return (0);
}

static void	handle_incorrect_arguments(t_minishell *minishell, char *av)
{
	if (get_path(minishell, av))
		exe_binary_error(minishell, get_path(minishell, av));
	else if (access(av, F_OK) == 0)
		is_a_directory(minishell, av);
	else
		no_path_file(minishell, av);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	ft_signals();
	init_minishell(&minishell, env); // в экзит хендлере не освобождается память для envp_var
	while (1)
	{
		if (ac > 1)
		{
			handle_incorrect_arguments(&minishell, av[1]);
			break ;
		}
		minishell.tmp->line = readline(PROMPT);
		if (!minishell.tmp->line)
			break ;
		else if (check_line(minishell))
			continue ;
		add_history(minishell.tmp->line);
		if (!lexer_main(&minishell, minishell.tmp->line))
			continue ;
		execute(&minishell);
	}
	exit_free(&minishell, minishell.exit_code);
	return (0);
}
