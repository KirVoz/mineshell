#include "minishell.h"



static void exe_solo(char *line)
{
    execute_command(line); // пока что тут просто строка которая подается без деления на что-то
}

void    execute(t_minishell *minishell, char *line)
{
    lex_line(minishell, line);
    if (minishell->cmd->pipes != 0 || minishell->cmd->semicoloumns != 0)
        //exe_many(minishell);
        printf("Not implemented yet\n");
    else
        exe_solo(line);
}