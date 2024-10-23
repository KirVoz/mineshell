/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:33:03 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 19:43:56 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static char	*allocate_cleaned_arg(char *arg, int *i, int *j)
{
	int		len;
	char	*cleaned_arg;

	if (!arg)
		return (NULL);
	len = ft_strlen(arg);
	cleaned_arg = (char *)malloc(len + 1);
	if (!cleaned_arg)
		return (NULL);
	*i = 0;
	*j = 0;
	if (arg[*i] == '-' || arg[*i] == '+')
		cleaned_arg[(*j)++] = arg[(*i)++];
	return (cleaned_arg);
}

static char	*clean_argument(char *arg)
{
	int		i;
	int		j;
	char	*cleaned_arg;

	cleaned_arg = allocate_cleaned_arg(arg, &i, &j);
	if (!cleaned_arg)
		return (NULL);
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			cleaned_arg[j++] = arg[i];
		else if (arg[i] != '\'' && arg[i] != '\"')
		{
			free(cleaned_arg);
			return (NULL);
		}
		i++;
	}
	cleaned_arg[j] = '\0';
	return (cleaned_arg);
}

static char	*validate_exit_arg(char *arg)
{
	if (!arg)
		return (NULL);
	if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
		return (NULL);
	return (clean_argument(arg));
}

static int	get_exit_code(char *command)
{
	long long	exit_value;

	exit_value = ft_atoll(command);
	if (errno == ERANGE)
		return (-1);
	if (exit_value > 255 || exit_value < 0)
		return ((int)(exit_value % 256));
	return ((int)exit_value);
}

void	execute_exit(t_minishell *minishell, int fd, t_cmd *cur)
{
	char	*command;

	(void)fd;
	if (cur->cmd[1] && cur->cmd[2] && !is_valid_number(cur->cmd[1]))
	{
		arg_count_error(minishell, "exit");
		return ;
	}
	if (minishell->tmp->is_child == 0)
		ft_putstr_fd("exit\n", 2);
	if (cur->cmd[1] != NULL)
	{
		command = validate_exit_arg(cur->cmd[1]);
		if (command == NULL || get_exit_code(command) == -1)
			numeric_error(minishell, "exit", cur->cmd[1]);
		else
			minishell->exit_code = get_exit_code(command);
		free(command);
	}
	else
		minishell->exit_code = 0;
	exit_free(minishell, minishell->exit_code);
}
