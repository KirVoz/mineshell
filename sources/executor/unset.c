#include "minishell.h"

static int find_env_index(char **env_array, const char *var_name)
{
    size_t var_name_len;
    int i;
    
    i = -1;
    var_name_len = ft_strlen(var_name);
    while (env_array[++i])
    {
        if (ft_strncmp(env_array[i], var_name, var_name_len) == 0
            && env_array[i][var_name_len] == '=')
            return i;
    }
    return -1;
}

static void remove_env_var(char **env_array, int index)
{
    int j;

    free(env_array[index]);
    j = index;
    while (env_array[j + 1] != NULL)
    {
        env_array[j] = env_array[j + 1];
        j++;
    }
    env_array[j] = env_array[j + 1]; // Ensure the last element is NULL
}

void execute_unset(t_minishell *minishell, int fd, t_cmd *cur)
{
    int i;
    int index;

    if (cur->cmd[1] == NULL)
    {
        ft_putstr_fd("unset: not enough arguments\n", fd);
        return;
    }
    i = 1;
    while (cur->cmd[i] != NULL)
    {
        index = find_env_index(minishell->env->envp_var, cur->cmd[i]);
        //printf("index: %d\n", index); //del
        if (index != -1)
        {
            remove_env_var(minishell->env->envp_var, index);
        }
        i++;
    }
    minishell->exit_code = 0;
}
