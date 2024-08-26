#include "minishell.h"

void    init_minishell(t_minishell *minishell, char **env)
{
    minishell->env = NULL; // Initialize as needed
    minishell->comms = (t_command *)malloc(sizeof(t_command) * 2);
}

int main(int ac, char **av, char **env) 
{
    t_minishell minishell;
    char *line;

    ft_signals();
    if (ac == 1)
    {
        while (1)
        {
            init_minishell(&minishell, env);
            line = readline(PROMPT);
            if (!line)
                break;
            if (line[0] != '\0')
            {
                add_history(line);
                lex_line(&minishell, line);
            }
            free(line);
        }
    }
    else
        printf("Minishell requires no arguments\n");
    return 0;
}
