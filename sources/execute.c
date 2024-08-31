#include "minishell.h"



static void exe_solo(t_minishell *minishell, char *line)
{
    execute_command(line, minishell); // пока что тут просто строка которая подается без деления на что-то
}

void    execute(t_minishell *minishell, char *line)
{
    lexer_main(line); // t_minishell; 29.08
    if (minishell->cmd->pipes != 0)
        //exe_many(minishell);
        printf("Not implemented yet\n");
    else
        exe_solo(minishell, line);
}
