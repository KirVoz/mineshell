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

void execute_exit(t_minishell *minishell, int fd, t_cmd *cur)
{
    int exit_code;

    (void)fd;
    /* Сначала надо проверить существование первого аргмента. Если первого нет, второго тоже не будет. 
    В ином случае, если у нас есть только комманда (то есть 0 - команда, 1 - NULL),
    условия попытается получить доступ к второму, которого нет, и выйдет за пределы памяти */
    if (cur->cmd[1] && cur->cmd[2])
    {
        arg_count_error(minishell, "exit");
        return ;
    }
    if (minishell->tmp->is_child == 0)
        ft_putstr_fd("exit\n", 1);
    if (cur->cmd[1] && ft_isalpha(cur->cmd[1][0]))
    {
        numeric_error(minishell, "exit",  cur->cmd[1]);
        exit_code = minishell->exit_code;
    }
    else if (cur->cmd[1])
        exit_code = ft_atoi(cur->cmd[1]);
    else
        exit_code = 0;
    exit_free(minishell, exit_code);
}


void execute_command(t_minishell *minishell, int fd, t_cmd *cur)
{
    int     i;
    char    *cmd_lower;

    i = 0;
    cmd_lower = str_to_lower(cur->cmd[0]);
    while (i < 7)
    {
        if (ft_strncmp(cmd_lower, commands[i].name, ft_strlen(commands[i].name)) == 0)
        {
            commands[i].func(minishell, fd, cur);
            free(cmd_lower);
            return;
        }
        i++;
    }
    free(cmd_lower);
}
