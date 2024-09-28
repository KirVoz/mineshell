#include "minishell.h"

int find_string_in_array(char **array, const char *str, size_t n)
{
    int i;
    
    i = 0;
    while (array[i])
    {
        if (ft_strncmp(array[i], str, n) == 0)
            return i;
        i++;
    }
    return -1;
}

void    execute_pwd(t_minishell *minishell, int fd, t_cmd *cur)
{
    int i;
    char *pwd;

    (void)cur;
    i = find_string_in_array(minishell->env->envp_var, "PWD=", 4);
    pwd = minishell->env->envp_var[i] + 4;
    ft_putstr_fd(pwd, fd);
    ft_putstr_fd("\n", fd);
    minishell->exit_code = 0;
}
