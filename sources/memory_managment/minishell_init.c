#include "minishell.h"
#include "lexer.h"

char *increment_shlvl(const char *shlvl)
{
    int level;
	int new_shlvl_len;
	int temp_level;
	char *new_shlvl;
	char *level_str;
	int i;
	
	level = ft_atoi(shlvl + 6);
    level++;
    if (level > 99)
    {
        level = 1;
        printf("SHLVL reset to 1\n");
    }
	new_shlvl_len = 6;
    temp_level = level;
    while (temp_level > 0)
    {
        new_shlvl_len++;
        temp_level /= 10;
    }
    new_shlvl = malloc(new_shlvl_len + 1);
    if (!new_shlvl)
        exit_fail("Failed to allocate memory for new SHLVL");
    ft_strcpy(new_shlvl, "SHLVL=");
    level_str = new_shlvl + 6;
    i = new_shlvl_len - 1;
    new_shlvl[i--] = '\0';
    while (level > 0)
    {
        new_shlvl[i--] = (level % 10) + '0';
        level /= 10;
    }
    return new_shlvl;
}

void init_envp(t_minishell *minishell, char **env)
{
    int i;
    int j;
    int len;

    len = 0;
    while (env[len])
        len++;
    minishell->env->envp_var = (char **)malloc(sizeof(char *) * (len + 1));
    if (minishell->env->envp_var == NULL)
        exit_fail("Failed to allocate memory for envp_var");
    i = 0;
    j = 0;
    while (env[i] != NULL)
    {
        if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
        {
            minishell->env->envp_var[j] = increment_shlvl(env[i]);
            if (minishell->env->envp_var[j] == NULL)
                exit_fail("Failed to allocate memory for incremented SHLVL");
            j++;
            i++;
            continue;
        }
        minishell->env->envp_var[j] = ft_strdup(env[i]);
        if (minishell->env->envp_var[j] == NULL)
            exit_fail("Failed to allocate memory for envp_var[i]");
        j++;
        i++;
    }
    minishell->env->envp_var[j] = NULL;
}

void	init_tmp(t_mem *tmp)
{
	tmp->line = NULL;
	tmp->tokens = NULL;
	tmp->heredoc_tmp = NULL;
	tmp->current_heredoc = 0;
}

t_cmd	*init_cmd_node(void)
{
	t_cmd	*empty_node;

	empty_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!empty_node)
		exit_fail("Failed to create new command node");
	empty_node->cmd = NULL;
	empty_node->heredoc = NULL;
	empty_node->infile = NULL;
	empty_node->outfile = NULL;
	empty_node->skipped_in = NULL;
	empty_node->skipped_out = NULL;
	empty_node->append = 0;
	empty_node->inpipe = 0;
	empty_node->outpipe = 0;
	empty_node->next = NULL;
	return (empty_node);
}

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env = (t_env *)malloc(sizeof(t_env));
	if (minishell->env == NULL)
		exit_fail("Failed to allocate memory for env");
	minishell->env->envp_var = NULL;
	init_envp(minishell, env);
	minishell->cmd = NULL;
	minishell->tmp = (t_mem *)malloc(sizeof(t_mem));
	if(!minishell->tmp)
		exit_fail("Failed to allocate memory for tmp");
	init_tmp(minishell->tmp);
	minishell->exit_code = 0;
}

