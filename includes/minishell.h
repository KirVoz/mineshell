#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
# include <fcntl.h>

# define PROMPT "minishell$ "
# define PROMPT_HEREDOC "heredoc> "
# define PROMPT_PIPE_HEREDOC "pipe heredoc>"

typedef struct s_minishell	t_minishell;

typedef enum s_redirect
{
	REDIR_IN,
	REDIR_OUT,
	APPEND_IN,
	APPEND_OUT,
}	t_redir;

typedef struct s_env
{
	t_list			*envp_var;
}					t_env;

typedef struct s_cmd
{
	char			**cmd;
	char			*infile;
	char			*outfile;
	char			mode; // o - overwrite, a - append, n - none
	int				inpipe;
	int				outpipe;
	int 			append;
	struct s_cmd	*next;
}					t_cmd;


typedef struct s_blin // сокращение от билдина
{
	char	*name;
	void	(*func)(t_minishell *, int);
}			t_blin;

typedef struct s_minishell
{
	t_env	*env;
	t_blin	*buildins;
	t_cmd	*cmd;
	int		exit_code;
}			t_minishell;

/*emulated comms*/
void		execute_cd(t_minishell *minishell, int fd);
void		execute_echo(t_minishell *minishell, int fd);
void		execute_pwd(t_minishell *minishell, int fd);
void		execute_export(t_minishell *minishell, int fd);
void		execute_unset(t_minishell *minishell, int fd);
void		execute_env(t_minishell *minishell, int fd);
void		execute_exit(t_minishell *minishell, int fd);
void		execute_command(char *cmd, t_minishell *minishell, int fd);

/*exe*/
void		execute(t_minishell *minishell, char **env);
/*signals*/
void		ft_signals(void);

// main.c
void		init_minishell(t_minishell *minishell, char **env);

// utils.c

/*error*/
void		exit_fail(const char *exit_message);
void		error_handler(t_minishell *minishell, char *error);
void		not_found(t_minishell *minishell, char *cmd);
int			syntax_error(t_minishell *minishell, char *token);
int			syntax_quote_error(t_minishell *minishell, char *token);

// path.c
char		*get_path(t_minishell *minishell, char *cmd);

#endif