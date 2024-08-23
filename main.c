#include "minishell.h"

void    init_minishell(t_minishell *minishell, char **env)
{
    int i;

    minishell->env = malloc(sizeof(t_env) * (MAX_CMD + 1));
    minishell->cmd = malloc(sizeof(t_cmd));
    minishell->cmd->cmd = NULL;
    minishell->cmd->pipe = 0;
    minishell->cmd->redirect = 0;
    minishell->cmd->file = NULL;
    minishell->cmd->append = 0;
    minishell->cmd->next = NULL;
    i = 0;
    while (env[i])
    {
        minishell->env[i].envp_var = strdup(env[i]);
        i++;
    }
    minishell->env[i].envp_var = NULL;
}

void    lex_line(t_minishell *minishell, char *line)
{
    int i;

    while  (*line)
    {
        if (isspase(*line))
            line++;
        if (isdigit_or_alpha(*line))
        {
            find_cmd(*line);
        }
    }
}

int main(int ac, char **av, char **env) 
{
    t_minishell minishell;
    char *line;

    if (ac == 1)
    {
        while (1)
        {
            line = readline(PROMPT);
            if (!line)
                break;
            if (line[0] != '\0')
            {
                add_history(line);
                printf("line: %s\n", line);
                lex_line(&minishell, line);
                init_minishell(&minishell, env);
            }
            free(line);
        }
    }
    else
        printf("Minishell requires no arguments\n");
    return 0;
}

