/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:16:03 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 20:04:56 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

t_blin	*get_commands(void)
{
	t_blin	*builtins;

	builtins = malloc(sizeof(t_blin) * 7);
	if (builtins == NULL)
		exit_fail("Failed to allocate memory for builtins");
	else
	{
		builtins[0] = (t_blin){"cd", execute_cd};
		builtins[1] = (t_blin){"echo", execute_echo};
		builtins[2] = (t_blin){"pwd", execute_pwd};
		builtins[3] = (t_blin){"export", execute_export};
		builtins[4] = (t_blin){"unset", execute_unset};
		builtins[5] = (t_blin){"env", execute_env};
		builtins[6] = (t_blin){"exit", execute_exit};
	}
	return (builtins);
}

void	execute_command(t_minishell *minishell, int fd, t_cmd *cur)
{
	int		i;
	char	*cmd_lower;
	t_blin	*commands;

	i = 0;
	commands = get_commands();
	cmd_lower = str_to_lower(cur->cmd[0]);
	while (i < 7)
	{
		if (ft_strncmp(cmd_lower, commands[i].name,
				ft_strlen(commands[i].name)) == 0)
		{
			commands[i].func(minishell, fd, cur);
			free(commands);
			free(cmd_lower);
			return ;
		}
		i++;
	}
	free(commands);
	free(cmd_lower);
}
