#include "minishell.h"

void execute_echo(t_minishell *minishell, int fd)
{
    int i = 1;
    int newline = 1;

    while (minishell->cmd->cmd[i] != NULL)
    {
        if (minishell->cmd->cmd[i][0] == '-' && minishell->cmd->cmd[i][1] == 'n')
        {
            int j = 2;
            while (minishell->cmd->cmd[i][j] == 'n')
                j++;
            if (minishell->cmd->cmd[i][j] == '\0')
            {
                newline = 0;
                i++;
                continue;
            }
        }
        break;
    }
    while (minishell->cmd->cmd[i] != NULL)
    {
        ft_putstr_fd(minishell->cmd->cmd[i], fd);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", fd);

    minishell->exit_code = 0;
}
