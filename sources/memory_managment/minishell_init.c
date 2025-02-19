/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:26:15 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 06:26:16 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static void	copy_env_var(t_minishell *minishell, char **env, int *i)
{
	if (ft_strncmp(env[*i], "SHLVL=", 6) == 0)
	{
		minishell->env[*i] = increment_shlvl(env[*i]);
		if (minishell->env[*i] == NULL)
			exit_fail("Failed to allocate memory for incremented SHLVL");
	}
	else
		minishell->env[*i] = allocate_dup(env[*i], "Env[j] in init_envp");
	(*i)++;
}

void	init_envp(t_minishell *minishell, char **env)
{
	int	i;
	int	len;
	int	shlvl;

	len = -1;
	i = -1;
	shlvl = 0;
	while (env[++len])
	{
		if (ft_strncmp(env[++i], "SHLVL=", 6) == 0)
			shlvl++;
	}
	if (shlvl == 0)
		len++;
	minishell->env = allocate_array(len, "Env in init_envp");
	i = 0;
	while (env[i] != NULL)
		copy_env_var(minishell, env, &i);
	if (shlvl == 0)
	{
		minishell->env[i] = ft_strdup("SHLVL=1");
		i++;
	}
	minishell->env[i] = NULL;
}

void	init_tmp(t_mem *tmp)
{
	tmp->line = NULL;
	tmp->tokens = NULL;
	tmp->heredoc_tmp = NULL;
	tmp->current_heredoc = 0;
	tmp->ws_tmp = NULL;
	tmp->ws_pipe_tmp = NULL;
	tmp->is_child = -1;
}

t_cmd	*init_cmd_node(size_t ws_count)
{
	t_cmd	*empty_node;

	empty_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!empty_node)
		exit_fail("Empty_node in init_cmd_node");
	empty_node->cmd = NULL;
	empty_node->heredoc = NULL;
	empty_node->files = NULL;
	empty_node->whitespace = allocate_whitespaces(ws_count,
			"Whitespace in init_cmd_node");
	empty_node->next = NULL;
	return (empty_node);
}

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env = NULL;
	init_envp(minishell, env);
	minishell->buildins = get_commands();
	minishell->cmd = NULL;
	minishell->tmp = (t_mem *)malloc(sizeof(t_mem));
	if (!minishell->tmp)
		exit_fail("Minishell->tmp in init_minishell");
	init_tmp(minishell->tmp);
	minishell->exit_code = 0;
	minishell->path = NULL;
	minishell->pipes = NULL;
	minishell->home = NULL;
}
