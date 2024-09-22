# include "minishell.h"
# include <string.h>

t_blin commands[7] = {
    { "echo", execute_echo },
    { "cd", execute_cd },
    { "pwd", execute_pwd },
    { "export", execute_export },
    { "unset", execute_unset },
    { "env", execute_env },
    { "exit", execute_exit },
};

void execute_echo(t_minishell *minishell, int fd)
{
    int i = 1;
    if (minishell->cmd->cmd[i] != NULL && ft_strncmp(minishell->cmd->cmd[i], "-n", 2) == 0)
        i++;
    while (minishell->cmd->cmd[i] != NULL)
    {
        ft_putstr_fd(minishell->cmd->cmd[i], fd);
        if (minishell->cmd->cmd[i + 1] != NULL)
            ft_putstr_fd(" ", fd);
        i++;
    }
    if (minishell->cmd->cmd[1] != NULL && ft_strncmp(minishell->cmd->cmd[1], "-n", 2) != 0)
        ft_putstr_fd("\n", fd);
}



void execute_export(t_minishell *minishell, int fd)
{
    int i;
    char *new_var;
    char *existing_var;
    int env_count;

    // Подсчёт количества переменных окружения
    for (env_count = 0; minishell->env->envp_var[env_count] != NULL; env_count++);

    if (minishell->cmd->cmd[1] != NULL)
    {
        new_var = minishell->cmd->cmd[1];
        // Проверка корректности переменной окружения
        if (strchr(new_var, '=') == NULL)
        {
            ft_putstr_fd("export: not a valid identifier\n", fd);
            return;
        }
        // Обновление существующей переменной
        for (i = 0; i < env_count; i++)
        {
            existing_var = minishell->env->envp_var[i];
            if (strncmp(existing_var, new_var, strchr(new_var, '=') - new_var) == 0)
            {
                free(minishell->env->envp_var[i]);
                minishell->env->envp_var[i] = ft_strdup(new_var);
                if (minishell->env->envp_var[i] == NULL)
                    exit_fail("Failed to allocate memory for envp_var element");
                return;
            }
        }
        // Добавление новой переменной
        minishell->env->envp_var = ft_realloc_exe(minishell->env->envp_var, sizeof(char *) * (env_count + 2)); // +1 для новой переменной и +1 для NULL
        if (minishell->env->envp_var == NULL)
            exit_fail("Failed to allocate memory for envp_var");
        minishell->env->envp_var[env_count] = ft_strdup(new_var);
        if (minishell->env->envp_var[env_count] == NULL)
            exit_fail("Failed to allocate memory for new_var");
        minishell->env->envp_var[env_count + 1] = NULL;
    }
    else
    {
        for (i = 0; i < env_count; i++)
        {
            ft_putstr_fd("declare -x ", fd);
            ft_putstr_fd(minishell->env->envp_var[i], fd);
            ft_putstr_fd("\n", fd);
        }
    }
    for (int k = 0; minishell->env->envp_var[k]; k++)
        printf("after export - %s\n", minishell->env->envp_var[k]);
}

void execute_env(t_minishell *minishell, int fd)
{
    int i;

    i = 0;
    while (minishell->env->envp_var[i] != NULL)
    {
        ft_putstr_fd("ENV  -   ", fd);
        ft_putstr_fd(minishell->env->envp_var[i], fd);
        ft_putstr_fd("\n", fd);
        i++;
    }
}

void execute_exit(t_minishell *minishell, int fd)
{
    (void)minishell;
    ft_putstr_fd("Executing 'exit' command\n", fd); // EXIT надо делать прирывающим цикл в мэйне иначе не выходит !!!
    exit(0);
}

void execute_command(char *cmd, t_minishell *minishell, int fd)
{
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(cmd, commands[i].name) == 0)
        {
            commands[i].func(minishell, fd);
            return;
        }
    }
    printf("Command not found: %s\n", cmd);
}
