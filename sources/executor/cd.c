#include "minishell.h"

static void update_env_var(t_minishell *minishell, char *var_name, char *new_value)
{
    int var_index;

    var_index = find_string_in_array(minishell->env->envp_var, var_name, ft_strlen(var_name));
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

static void update_pwd_vars(t_minishell *minishell, char *old_pwd, char *new_path)
{
    update_env_var(minishell, "OLDPWD=", old_pwd);
    update_env_var(minishell, "PWD=", new_path);
    printf("%s\n", new_path);
}

static void change_to_home_directory(t_minishell *minishell)
{
    int home_index;
    char *new_path;
    char *old_pwd;

    home_index = find_string_in_array(minishell->env->envp_var, "HOME=", 5);
    if (home_index == -1) {
        printf("HOME environment variable not found\n");
        return;
    }
    new_path = ft_strdup(minishell->env->envp_var[home_index] + 5);
    old_pwd = ft_strdup(minishell->env->envp_var[find_string_in_array(minishell->env->envp_var, "PWD=", 4)] + 4);
    if (old_pwd == NULL)
        exit_fail("Failed to allocate memory for old_pwd");
    update_pwd_vars(minishell, old_pwd, new_path);
    free(old_pwd);
}

static void change_directory(t_minishell *minishell, char *new_path)
{
    char *old_pwd;
    char cwd[1024];

    if (chdir(new_path))
    {
        printf("Failed to change directory\n");
        free(new_path);
        return;
    }
    old_pwd = ft_strdup(minishell->env->envp_var[find_string_in_array(minishell->env->envp_var, "PWD=", 4)] + 4);
    if (old_pwd == NULL)
    {
        free(new_path);
        exit_fail("Failed to allocate memory for old_pwd");
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        free(new_path);
        free(old_pwd);
        printf("Failed to get current working directory\n");
        return;
    }
    update_pwd_vars(minishell, old_pwd, cwd);
    free(old_pwd);
    free(new_path);
}

void execute_cd(t_minishell *minishell, int fd)
{
    (void)fd;
    char *new_path;

    if (minishell->cmd->cmd[1] == NULL)
    {
        if (chdir(minishell->env->envp_var[find_string_in_array(minishell->env->envp_var, "HOME=", 5)] + 5))
            printf("Failed to change directory\n");
        change_to_home_directory(minishell);
    }
    else
    {
        new_path = ft_strdup(minishell->cmd->cmd[1]);
        change_directory(minishell, new_path);
    }
    minishell->exit_code = 0;
}
