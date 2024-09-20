#include "minishell.h"

void    execute_pwd(t_minishell *minishell, int fd)
{
    char *cwd;
    size_t size = 1024;

    (void)minishell;
    cwd = (char *)malloc(size * sizeof(char));
    if (cwd == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    if (getcwd(cwd, size) == NULL)
    {
        perror("getcwd() error");
        free(cwd);
        exit(EXIT_FAILURE);
    }
    ft_putstr_fd(cwd, fd);
    ft_putstr_fd("\n", fd);
    free(cwd);
}
