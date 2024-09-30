#include "minishell.h"

void execute_env(t_minishell *minishell, int fd, t_cmd *cur)
{
    int i;

    (void)fd;
    i = 0;
    if (cur->cmd[1])
    {
        arg_count_error(minishell, "env");
        return ;
    }
    while (minishell->env[i] != NULL)
    {
        ft_putstr_fd(minishell->env[i], fd);
        ft_putstr_fd("\n", fd);
        i++;
    }
    minishell->exit_code = 0;
}