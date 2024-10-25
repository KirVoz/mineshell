/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:13:28 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:13:33 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_string_in_array(char **array, const char *str, size_t n)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], str, n) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	execute_pwd(t_minishell *minishell, int fd, t_cmd *cur)
{
	int		i;
	char	*pwd;
	char	cwd[1024];

	(void)cur;
	i = find_string_in_array(minishell->env, "PWD=", 4);
	if (i == -1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			minishell->exit_code = 1;
			return;
		}
		update_env_var(minishell, "PWD=", cwd, ft_array_len(minishell->env));
	}
	i = find_string_in_array(minishell->env, "PWD=", 4);
	pwd = minishell->env[i] + 4;
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	minishell->exit_code = 0;
}
