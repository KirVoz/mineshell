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
