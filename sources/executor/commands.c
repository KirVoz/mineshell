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

void execute_exit(t_minishell *minishell, int fd)
{
    int exit_code;

    (void)fd;
    /* Сначала надо проверить существование первого аргмента. Если первого нет, второго тоже не будет. 
    В ином случае, если у нас есть только комманда (то есть 0 - команда, 1 - NULL),
    условия попытается получить доступ к второму, которого нет, и выйдет за пределы памяти */
    if (minishell->cmd->cmd[1] && minishell->cmd->cmd[2])
    {
        arg_count_error(minishell, "exit");
        return ;
    }
    if (minishell->cmd->cmd[1])
        exit_code = ft_atoi(minishell->cmd->cmd[1]);
    else
        exit_code = 0;
    ft_putstr_fd("exit\n", 1);
    exit_free(minishell, exit_code);
}


void execute_command(char *cmd, t_minishell *minishell, int fd)
{
    int i;

    i = 0;
    while (i < 7)
    {
        if (ft_strncmp(cmd, commands[i].name, ft_strlen(commands[i].name)) == 0)
        {
            commands[i].func(minishell, fd);
            return;
        }
        i++;
    }
    printf("Command not found: %s\n", cmd);
}
