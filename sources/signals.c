/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:17:54 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:17:55 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		// printf("g_child: %d\n", g_child);
		printf("\n");
		if (!g_child)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

static void	ctrl_backslash(int signal)
{
	if (signal == SIGQUIT)
	{
		if (g_child)
			printf("Quit: 3\n");
	}
}

// void	ft_default_signals(void)
// {
// 	struct sigaction	sa;

//     printf("Restoring default signal handling in child process\n");
// 	rl_catch_signals = 0;
// 	sa.sa_handler = SIG_DFL;
// 	sa.sa_flags = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sa.sa_handler = ctrl_backslash;
// 	sigaction(SIGQUIT, &sa, NULL);
// }

void	ft_signals(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sa.sa_handler = ctrl_c;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = ctrl_backslash;
	sigaction(SIGQUIT, &sa, NULL);
}
