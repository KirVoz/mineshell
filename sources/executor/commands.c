# include "minishell.h"
#include "lexer.h"
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
    int newline = 1;

    while (minishell->cmd->cmd[i] != NULL && ft_strncmp(minishell->cmd->cmd[i], "-n", 2) == 0)
    {
        newline = 0;
        i++;
    }
    while (minishell->cmd->cmd[i] != NULL)
    {
        ft_putstr_fd(minishell->cmd->cmd[i], fd);
        if (minishell->cmd->cmd[i + 1] != NULL)
            ft_putstr_fd(" ", fd);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", fd);
    minishell->exit_code = 0;
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
    minishell->exit_code = 0;
}

void execute_exit(t_minishell *minishell, int fd)
{
    int exit_code;

    (void)fd;
    // (void)minishell;
    // ft_putstr_fd("Executing 'exit' command\n", fd); // EXIT надо делать прирывающим цикл в мэйне иначе не выходит !!!
    if (minishell->cmd->cmd[2])
    {
        arg_count_error(minishell, "exit");
        return ;
    }
    if (minishell->cmd->cmd[1])
        exit_code = ft_atoi(minishell->cmd->cmd[1]);
    else
        exit_code = 0;
    ft_putstr_fd("exit\n", 1);
    free_minishell(minishell);
    exit_free(minishell, exit_code);
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
