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
    { "exit ", execute_exit },
};

void execute_exit(t_minishell *minishell, int fd)
{
    int exit_code;

    (void)fd;
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
