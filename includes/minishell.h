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
# define PROMPT_HEREDOC "> "

typedef struct s_minishell	t_minishell;

typedef struct s_env
{
	char			**envp_var;
}					t_env;

typedef struct s_cmd
{
	char			**cmd;
	char			**heredoc;
	char			*infile;
	char			*outfile;
	t_list			*skipped_in;
	t_list			*skipped_out;
	int 			append;
	int				inpipe;
	int				outpipe;
	struct s_cmd	*next;
}					t_cmd;


typedef struct s_blin // сокращение от билдина
{
	char	*name;
	void	(*func)(t_minishell *, int);
}			t_blin;

typedef struct s_mem
{
	char	**tokens;
	char	***heredoc_tmp;
	int		current_heredoc;
}			t_mem;


typedef struct s_minishell
{
	t_env	*env;
	t_blin	*buildins;
	t_cmd	*cmd;
	t_mem	*tmp;
	int		exit_code;
}			t_minishell;


// minishell_init.c
void		init_envp(t_minishell *minishell, char **env);
void		init_tmp(t_mem *tmp);
t_cmd		*init_cmd_node(void);
void		init_minishell(t_minishell *minishell, char **env);


/*utils.c*/
void		*ft_realloc_exe(void *ptr, size_t size);
/*emulated comms*/
int			find_string_in_array(char **array, const char *str, size_t n);
void		execute_cd(t_minishell *minishell, int fd);
void		execute_echo(t_minishell *minishell, int fd);
void		execute_pwd(t_minishell *minishell, int fd);
void		execute_export(t_minishell *minishell, int fd);
void		execute_unset(t_minishell *minishell, int fd);
void		execute_env(t_minishell *minishell, int fd);
void		execute_exit(t_minishell *minishell, int fd);
void		execute_command(char *cmd, t_minishell *minishell, int fd);

/*exe*/
void		execute(t_minishell *minishell);
/*signals*/
void		ft_signals(void);

// main.c

// utils.c
int			count_str(char **str);
/*error*/
void		exit_fail(const char *exit_message);
void		error_handler(t_minishell *minishell, char *error);
void		not_found(t_minishell *minishell, char *cmd);
void   		no_file(t_minishell *minishell, char *filename);
int			syntax_error(t_minishell *minishell, char *token);
int			syntax_quote_error(t_minishell *minishell, char *token);

// path.c
char		*get_path(t_minishell *minishell, char *cmd);

#endif