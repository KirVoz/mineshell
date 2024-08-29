#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "lexer.h"
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell$ "
# define PROMPT_HEREDOC "heredoc> "
# define MAX_CMD 1024


typedef void	(*action)(void);

typedef enum s_redirect
{
	REDIR_IN,
	REDIR_OUT,
	APPEND_IN,
	APPEND_OUT,
}				t_redir;

typedef struct s_env
{
	char		**envp_var; // если реализовывать через списки то не надо будет волноватся о перевыделение памяти
}				t_env;

// typedef struct  s_list
// {
//     char    *content;
//     struct s_list *next;
// }               t_list;

typedef struct 	s_cmd
{
	t_list		*m_av; // изменил на связный список
	int			m_ac;
	int			pipes;
}				t_cmd;

typedef struct 	s_blin // сокращение от билдина
{
	char *name;
	void (*func)(void);
}				t_blin;

typedef struct 	s_minishell
{
	t_env		*env;
	t_blin		*buildins;
	t_cmd		*cmd;
	int			exit_code;
}				t_minishell;

/*emulated comms*/
void			execute_ls(void);
void			execute_cd(void);
void			execute_echo(void);
void			execute_pwd(void);
void			execute_export(void);
void			execute_unset(void);
void			execute_env(void);
void			execute_exit(void);
void			execute_command(char *cmd);
/*exe*/
void			execute(t_minishell *minishell, char *line);
/*signals*/
void			ft_signals(void);
// utils.c
bool			is_space(char c);
bool			is_digit_or_alpha(char c);

void			execute_ls(void);
void			execute_cd(void);
// main.c
void			init_minishell(t_minishell *minishell, char **env);

#endif