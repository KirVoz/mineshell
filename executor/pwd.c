#include "minishell.h"

void    execute_pwd(t_minishell *minishell, int fd)
{
    int i;
    for (int j = 0; minishell->env->envp_var[j]; j++)
        printf("%dpwd env -> %s\n", j, minishell->env->envp_var[j]);
    i = find_string_in_array(minishell->env->envp_var, "PWD=", 4);
    (void)i;
    ft_putstr_fd(minishell->env->envp_var[15], fd);
    ft_putstr_fd("\n", fd);
}
