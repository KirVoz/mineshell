# include "minishell.h"

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
