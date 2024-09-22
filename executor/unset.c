#include "minishell.h"

static int  find_env_index(char **env_array, const char *var_name)
{
    size_t var_name_len;
    int i;
    
    i = -1;
    var_name_len = ft_strchr(var_name, '=') - var_name;
    while (env_array[++i])
    {
        if (ft_strncmp(env_array[i], var_name, var_name_len) == 0
            && env_array[i][var_name_len] == '=')
            return i;
    }
    return -1;
}

void    execute_unset(t_minishell *minishell, int fd)
{
    int i;
    int j;
    int index;

    i = 0;
    if (minishell->cmd->cmd[1] == NULL)
    {
        ft_putstr_fd("unset: not enough arguments\n", fd);
        return;
    }
    while (minishell->cmd->cmd[++i] != NULL)
    {
        index = find_env_index(minishell->env->envp_var, minishell->cmd->cmd[i]);
        if (index != -1)
        {
            free(minishell->env->envp_var[index]);
            j = index;
            while (minishell->env->envp_var[j + 1] != NULL)
            {
                minishell->env->envp_var[j] = minishell->env->envp_var[j + 1];
                j++;
            }
            minishell->env->envp_var[j] = NULL;
        }
    }
}
