/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:45:38 by kvoznese          #+#    #+#             */
/*   Updated: 2024/10/09 17:47:28 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	ft_check_valid_symbol(char *new_var, int i, int mode)
{
	if (mode)
	{
		if (new_var[i] == '@' || new_var[i] == '*' || new_var[i] == '^'
			|| new_var[i] == '?' || new_var[i] == '-' || new_var[i] == '$'
			|| new_var[i] == '!' || new_var[i] == '~' || new_var[i] == '.'
			|| new_var[i] == '{' || new_var[i] == '}' || new_var[i] == '#')
			return (1);
		else if (new_var[i] == '+' && new_var[i + 1] != '=')
			return (1);
		else if (new_var[i] == '+' && new_var[i + 1] == '=')
			return (2);
		else
			return (0);
	}
	else
	{
		if (new_var[i] >= '0' && new_var[i] <= '9')
			return (1);
		else
			return (0);
	}
}

void	declare_env_var(t_minishell *minishell, int fd)
{
	char	*declare;
	size_t	env_count;
	size_t	i;

	env_count = array_len(minishell->env);
	i = -1;
	while (++i < env_count)
	{
		declare = construct_declare(minishell->env[i]);
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(declare, fd);
		ft_putstr_fd("\n", 1);
		free(declare);
	}
}

char	*construct_declare(char *env_var)
{
	char	*new_var;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_var = allocate_string(ft_strlen(env_var) + 3, "New_var");
	while (env_var[i] != '=')
		new_var[j++] = env_var[i++];
	new_var[j++] = env_var[i++];
	new_var[j++] = '"';
	while (env_var[i])
		new_var[j++] = env_var[i++];
	new_var[j++] = '"';
	new_var[j] = '\0';
	return (new_var);
}
