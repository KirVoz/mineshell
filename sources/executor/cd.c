#include "minishell.h"

static void update_env_var(t_minishell *minishell, const char *var_name, const char *new_value)
{
    int var_index = find_string_in_array(minishell->env->envp_var, var_name, ft_strlen(var_name));
    if (var_index != -1)
    {
        free(minishell->env->envp_var[var_index]);
        minishell->env->envp_var[var_index] = ft_strjoin(var_name, new_value);
    }
}

static void update_pwd_vars(t_minishell *minishell, const char *old_pwd, const char *new_path)
{
    update_env_var(minishell, "OLDPWD=", old_pwd);
    update_env_var(minishell, "PWD=", new_path);
    printf("%s\n", new_path);
}

static void change_directory(t_minishell *minishell, const char *new_path)
{
    char cwd[1024];
    char *old_pwd = ft_strdup(minishell->env->envp_var[find_string_in_array(minishell->env->envp_var, "PWD=", 4)] + 4);
    if (chdir(new_path) || getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("minishell: cd: %s: No such file or directory\n", new_path);
        minishell->exit_code = 1;
    }
    else
    {
        update_pwd_vars(minishell, old_pwd, cwd);
        minishell->exit_code = 0;
    }
    free(old_pwd);
}

static void change_to_home_directory(t_minishell *minishell)
{
    int home_index = find_string_in_array(minishell->env->envp_var, "HOME=", 5);
    if (home_index == -1)
    {
        printf("HOME environment variable not found\n");
        minishell->exit_code = 1;
        return;
    }
    change_directory(minishell, minishell->env->envp_var[home_index] + 5);
}

void execute_cd(t_minishell *minishell, int fd)
{
    (void)fd;
    if (minishell->cmd->cmd[1] == NULL)
        change_to_home_directory(minishell);
    else
        change_directory(minishell, minishell->cmd->cmd[1]);
}
