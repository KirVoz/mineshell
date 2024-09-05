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

// Function to execute the 'cd' command
void execute_cd(t_minishell *minishell)
{
    (void)minishell;
    printf("Executing 'cd' command\n");
}

void execute_echo(t_minishell *minishell)
{
    (void)minishell;
    printf("Executing 'echo' command\n");
}

void execute_pwd(t_minishell *minishell)
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
    if (printf("%s\n", cwd) < 0)
    {
        perror("Failed to write to stdout");
        free(cwd);
        exit(EXIT_FAILURE);
    }
    free(cwd);
}

void execute_export(t_minishell *minishell)
{
    (void)minishell;
    printf("Executing 'export' command\n");
}

void execute_unset(t_minishell *minishell)
{
    (void)minishell;
    printf("Executing 'unset' command\n");
}

void execute_env(t_minishell *minishell)
{
    t_list *current = minishell->env->envp_var;
    while (current != NULL)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
}

void execute_exit(t_minishell *minishell)
{
    (void)minishell;
    printf("Executing 'exit' command\n"); // EXIT надо делать прирывающим цикл в мэйне иначе не выходит !!!
}

void execute_command(char *cmd, t_minishell *minishell)
{
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(cmd, commands[i].name) == 0)
        {
            commands[i].func(minishell);
            return;
        }
    }
    printf("Command not found: %s\n", cmd);
}
