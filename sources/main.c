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

static void	read_and_process_commands(t_minishell *minishell)
{
	while (1)
	{
		minishell->tmp->line = readline(PROMPT);
		if (!minishell->tmp->line)
		{
			printf("\e[A\e[11Cexit\n");
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

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	ft_signals();
	init_minishell(&minishell, env);
	if (ac > 1)
	{
		handle_incorrect_arguments(&minishell, av[1]);
		exit_free(&minishell, (&minishell)->exit_code);
	}
	read_and_process_commands(&minishell);
	exit_free(&minishell, (&minishell)->exit_code);
	return (0);
}
