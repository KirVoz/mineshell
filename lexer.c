# include "minishell.h"

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
    if (strcmp(cmd, "ls") == 0)
        execute_ls();
    else if (strcmp(cmd, "cd") == 0)
        execute_cd();
    else if (strcmp(cmd, "echo") == 0)
        execute_echo();
    else if (strcmp(cmd, "pwd") == 0)
        execute_pwd();
    else if (strcmp(cmd, "export") == 0)
        execute_export();
    else if (strcmp(cmd, "unset") == 0)
        execute_unset();
    else if (strcmp(cmd, "env") == 0)
        execute_env();
    else if (strcmp(cmd, "exit") == 0)
        execute_exit();
    else
        printf("Command not found: %s\n", cmd);
}

void lex_line(t_minishell *minishell, char *line)
{
    char cmd[MAX_CMD];
    int i = 0;

    while (*line)
    {
        while (*line && isspace(*line))
            line++;
        i = 0;
        while (*line && *line != ';' && !isspace(*line))
        {
            cmd[i++] = *line++;
        }
        cmd[i] = '\0';
        if (i > 0)
        {
            execute_command(cmd);
        }
        while (*line && (isspace(*line) || *line == ';'))
            line++;
    }
}
