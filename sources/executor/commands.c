# include "minishell.h"
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

// static void	ft_putstr_fd(char *str, int fd)
// {
// 	write(fd, str, ft_strlen(str));
// }
// Function to execute the 'cd' command
void execute_cd(t_minishell *minishell, int fd)
{
    char *path;

    if (minishell->cmd->cmd[1] == NULL)
    {
    path = getenv("HOME");
        if (path == NULL)
        {
            ft_putstr_fd("cd: HOME not set\n", fd);
            return;
        }
    }
    else
        path = minishell->cmd->cmd[1];
    if (chdir(path) != 0)
        perror("cd");
}

void execute_echo(t_minishell *minishell, int fd)
{
    (void)minishell;
    ft_putstr_fd("Executing 'echo' command\n", fd);
}

void execute_pwd(t_minishell *minishell, int fd)
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

void execute_export(t_minishell *minishell, int fd)
{
    (void)minishell;
    ft_putstr_fd("Executing 'export' command\n", fd);
}

void execute_unset(t_minishell *minishell, int fd)
{
    (void)minishell;
    ft_putstr_fd("Executing 'unset' command\n", fd);
}

void execute_env(t_minishell *minishell, int fd)
{
    t_list *current = minishell->env->envp_var;
    while (current != NULL)
    {
        ft_putstr_fd((char *)current->content, fd);
        current = current->next;
    }
}

void execute_exit(t_minishell *minishell, int fd)
{
    (void)minishell;
    ft_putstr_fd("Executing 'exit' command\n", fd); // EXIT надо делать прирывающим цикл в мэйне иначе не выходит !!!
    exit(0);
}

void execute_command(char *cmd, t_minishell *minishell, int fd)
{
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(cmd, commands[i].name) == 0)
        {
            commands[i].func(minishell, fd);
            return;
        }
    }
    printf("Command not found: %s\n", cmd);
}
