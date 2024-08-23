#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>

# define PROMPT "minishell$ "
# define MAX_CMD 1024

typedef struct  s_env
{
    char    *envp_var;
}               t_env;

typedef struct  s_cmd
{
    char    *cmd;
    int     pipe;
    int     redirect;
    char    *file;
    int     append;
    struct s_cmd   *next;
}               t_cmd;

typedef struct  s_minishell
{
    t_env *env;
    t_cmd *cmd;
}               t_minishell;



# endif