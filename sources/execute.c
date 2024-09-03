#include "minishell.h"
#include "lexer.h"



// static void exe_solo(t_minishell *minishell, char *line)
// {
//     execute_command(line, minishell); // пока что тут просто строка которая подается без деления на что-то
// }

void    execute(t_minishell *minishell, char *line)
{
    lexer_main(minishell, line);
    // if (minishell->cmd->pipes != 0)
    //     //exe_many(minishell);
    //     printf("Not implemented yet\n");
    // else
    //     exe_solo(minishell, line);
}
