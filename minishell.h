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
# include <ctype.h>
# include <signal.h>

# define PROMPT "minishell$ "
# define MAX_CMD 1024

typedef void (*action)(void);

typedef struct  s_env
{
    char    *envp_var;
}               t_env;

/*typedef struct  s_cmd
{
    char    *cmd;
    int     pipe;
    int     redirect;
    char    *file;
    int     append;
    struct s_cmd   *next;
}               t_cmd;*/

typedef struct s_command
{
    const char* name;
    action foo;
} t_command;

typedef struct  s_minishell
{
    t_env *env;
    //t_cmd *cmd;
    t_command *comms;
}               t_minishell;

/*emulated comms*/
void execute_ls(void);
void execute_cd(void);
void execute_echo(void);
void execute_pwd(void);
void execute_export(void);
void execute_unset(void);
void execute_env(void);
void execute_exit(void);
/*signals*/
void    ft_signals(void);
// utils.c
bool    is_space(char c);
bool    is_digit_or_alpha(char c);
// lexer.c
void    lex_line(t_minishell *minishell, char *line);
void    execute_ls(void);
void    execute_cd(void);
// main.c
void    init_minishell(t_minishell *minishell, char **env);

#endif