# include "minishell.h"
# include <string.h>

t_blin commands[8] = {
    { "echo", execute_echo },
    { "cd", execute_cd },
    { "pwd", execute_pwd },
    { "export", execute_export },
    { "unset", execute_unset },
    { "env", execute_env },
    { "exit", execute_exit },
    { "ls", execute_ls },
};

// Function to execute the 'ls' command
void execute_ls(void)
{
    printf("Executing 'ls' command\n");
}

// Function to execute the 'cd' command
void execute_cd(void)
{
    printf("Executing 'cd' command\n");
}

void execute_echo(void)
{
    printf("Executing 'echo' command\n");
}

void execute_pwd(void)
{
    printf("Executing 'pwd' command\n");
}
void execute_export(void)
{
    printf("Executing 'export' command\n");
}
void execute_unset(void)
{
    printf("Executing 'unset' command\n");
}
void execute_env(void)
{
    printf("Executing 'env' command\n");
}

void execute_exit(void)
{
    printf("Executing 'exit' command\n"); // EXIT надо делать прирывающим цикл в мэйне иначе не выходит !!!
}

void execute_command(char *cmd)
{
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(cmd, commands[i].name) == 0)
        {
            commands[i].func();
            return;
        }
    }
    printf("Command not found: %s\n", cmd);
}
