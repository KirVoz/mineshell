/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:22:48 by aaleksee          #+#    #+#             */
/*   Updated: 2024/10/09 17:17:46 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static int	check_line(t_minishell minishell)
{
	if (minishell.tmp->line[0] == '\0')
	{
		free(minishell.tmp->line);
		return (1);
	}
	return (0);
}

static void	process_arguments(int ac, char **av, t_minishell *minishell)
{
	if (ac > 1)
	{
		handle_incorrect_arguments(minishell, av[1]);
		exit(1);
	}
}

static void	read_and_process_commands(t_minishell *minishell)
{
	while (1)
	{
		minishell->tmp->line = readline(PROMPT);
		if (!minishell->tmp->line)
		{
			printf("exit\n");
			exit_free(minishell, 0);
			break ;
		}
		else if (check_line(*minishell))
			continue ;
		add_history(minishell->tmp->line);
		if (!lexer_main(minishell, minishell->tmp->line))
			continue ;
		execute(minishell);
	}
}

static void	run_minishell(t_minishell *minishell, char **env)
{
	ft_signals();
	init_minishell(minishell, env);
	read_and_process_commands(minishell);
	exit_free(minishell, minishell->exit_code);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		ft_signals();
		init_minishell(&minishell, env);
		minishell.tmp->line = ft_strdup(av[2]);
		while (1)
		{
			if (check_line(minishell))
				continue ;
			else if (!lexer_main(&minishell, minishell.tmp->line))
				exit(minishell.exit_code);
			execute(&minishell);
			exit_free(&minishell, minishell.exit_code);
		}
	}
	else
	{
		process_arguments(ac, av, &minishell);
		run_minishell(&minishell, env);
	}
	return (0);
}
