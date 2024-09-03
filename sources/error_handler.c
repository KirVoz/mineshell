#include "minishell.h"

void    error_handler(char *error, t_minishell *minishell)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(error, 2);
    ft_putstr_fd("\n", 2);
    minishell->exit_code = 1;
    exit (1);
}
