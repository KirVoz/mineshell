#include "minishell.h"

void execute_env(t_minishell *minishell, int fd, t_cmd *cur)
{
    int i;

    (void)fd;
    i = 1;
	while (cur->cmd[i] == '\0' && cur->cmd[i] != NULL)
    {
        arg_count_error(minishell, "env");
		i++;
        return ;
    }
    while (minishell->env[i] != NULL)
    {
        ft_putstr_fd(minishell->env[i], fd);
        ft_putstr_fd("\n", fd);
        i++;
    }
	printf("I - %d\n", i);	
    minishell->exit_code = 0;
}
