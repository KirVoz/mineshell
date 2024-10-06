/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese < kvoznese@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:22:48 by aaleksee          #+#    #+#             */
/*   Updated: 2024/10/06 12:46:57 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static void	handle_incorrect_arguments(t_minishell *minishell, char *av)
{
	struct stat	stat_buf;

	stat(av, &stat_buf);
	if (get_path(minishell, av) && !S_ISDIR(stat_buf.st_mode))
		exe_binary_error(minishell, get_path(minishell, av));
	else if (access(av, F_OK) == 0 && S_ISDIR(stat_buf.st_mode))
		is_a_directory(minishell, av, 'm');
	else
		no_path_file(minishell, av);
}

static int	check_line(t_minishell minishell)
{
	if (minishell.tmp->line[0] == '\0')
	{
		free(minishell.tmp->line);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	ft_signals();
	init_minishell(&minishell, env);
	while (1)
	{
		if (ac > 1)
		{
			handle_incorrect_arguments(&minishell, av[1]);
			break ;
		}
		minishell.tmp->line = readline(PROMPT);
		if (!minishell.tmp->line)
		{
			printf("exit\n");
			exit_free(&minishell, 0);
			break ;
		}
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
