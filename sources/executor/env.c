#include "minishell.h"

void execute_env(t_minishell *minishell, int fd)
{
    int i;

    i = 0;
    if (minishell->cmd->cmd[1])
    {
        arg_count_error(minishell, "env");
        return ;
    }
    while (minishell->env->envp_var[i] != NULL)
    {
        ft_putstr_fd(minishell->env->envp_var[i], fd);
        ft_putstr_fd("\n", fd);
        i++;
    }
    minishell->exit_code = 0;
}