#include "minishell.h"

int find_string_in_array(char **array, const char *str, size_t n)
{
    int i;
    
    i = 0;
    while (array[i])
    {
        if (ft_strncmp(array[i], str, n) == 0)
            return i;
        i++;
    }
    return -1;
}

static void update_env_var(t_minishell *minishell, char *var_name, char *new_value)
{
    int var_index;

    var_index = find_string_in_array(minishell->env->envp_var, var_name, ft_strlen(var_name));
    printf("update env - index = %d\n", var_index);
    if (var_index != -1)
    {
        free(minishell->env->envp_var[var_index]);
        minishell->env->envp_var[var_index] = ft_strjoin(var_name, new_value);
    }
    else
    {
        printf("Variable %s not found\n", var_name);
    }
}

static void change_pwd(t_minishell *minishell, char *new_path)
{
    int home_index;

    for (int j = 0; minishell->env->envp_var[j]; j++)
    {
        printf("MY ENV = %s\n", minishell->env->envp_var[j]);
    }
    home_index = find_string_in_array(minishell->env->envp_var, "PWD=", 4);
    printf("home_index = %d\n", home_index);
    if (home_index != -1)
    {
        free(minishell->env->envp_var[home_index]);
        minishell->env->envp_var[home_index] = new_path;
    }
    else
    {
        printf("Variable PWD not found\n");
    }
}

void execute_cd(t_minishell *minishell, int fd)
{
    (void)fd;
    char *new_path;
    int home_index;
    char *old_pwd;

    if (minishell->cmd->cmd[1] == NULL)
    {
        home_index = find_string_in_array(minishell->env->envp_var, "HOME=", 5);
        new_path = ft_strdup(minishell->env->envp_var[home_index] + 5);
        old_pwd = ft_strdup(minishell->env->envp_var[find_string_in_array(minishell->env->envp_var, "PWD=", 4)] + 4);
        if (old_pwd == NULL)
            exit_fail("Failed to allocate memory for old_pwd");
        update_env_var(minishell, "OLDPWD=", old_pwd);
        update_env_var(minishell, "PWD=", new_path);
    }
    else
    {
        new_path = ft_strdup(minishell->cmd->cmd[1]);
    }
    change_pwd(minishell, new_path);
    printf("%s\n", new_path);
}
