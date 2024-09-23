#include "minishell.h"

static void update(t_minishell *minishell, const char *new_var, int env_count)
{
        minishell->env->envp_var = ft_realloc_exe(minishell->env->envp_var, sizeof(char *)
            * (env_count + 2)); // +1 для новой переменной и +1 для NULL
    if (minishell->env->envp_var == NULL)
        exit_fail("Failed to allocate memory for envp_var");
    minishell->env->envp_var[env_count] = ft_strdup(new_var);
    if (minishell->env->envp_var[env_count] == NULL)
        exit_fail("Failed to allocate memory for new_var");
    minishell->env->envp_var[env_count + 1] = NULL;
}

static void add_or_update_env_var(t_minishell *minishell, const char *new_var)
{
    int i;
    char *existing_var;
    int env_count;
    size_t var_name_len;

    env_count = count_str(minishell->env->envp_var);
    var_name_len = ft_strchr(new_var, '=') - new_var;
    printf("var_name_len: %zu\n", var_name_len);

    i = -1;
    while (++i < env_count)
    {
        existing_var = minishell->env->envp_var[i];
        if (ft_strncmp(existing_var, new_var, var_name_len) == 0
            && (existing_var[var_name_len] == '=' || existing_var[var_name_len] == '\0'))
        {
            free(minishell->env->envp_var[i]);
            minishell->env->envp_var[i] = ft_strdup(new_var);
            if (minishell->env->envp_var[i] == NULL)
                exit_fail("Failed to allocate memory for envp_var element");
            return;
        }
    }
    update(minishell, new_var, env_count);
}

void execute_export(t_minishell *minishell, int fd)
{
    int i;
    char *new_var;
    int env_count;

    env_count = count_str(minishell->env->envp_var);
    if (minishell->cmd->cmd[1] != NULL)
    {
        new_var = minishell->cmd->cmd[1];
        if (ft_strchr(new_var, '=') == NULL)
        {
            ft_putstr_fd("export: not a valid identifier\n", fd);
            return;
        }
        add_or_update_env_var(minishell, new_var);
    }
    else
    {
        i = -1;
        while (++i < env_count)
        {
            ft_putstr_fd("declare -x ", fd);
            ft_putstr_fd(minishell->env->envp_var[i], fd);
            ft_putstr_fd("\n", fd);
        }
    }
    minishell->exit_code = 0;
}
