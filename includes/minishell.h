#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <ctype.h>
# include "../libraries/readline_lib/include/readline/readline.h"
# include "../libraries/readline_lib/include/readline/history.h"
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>

# define PROMPT "minishell$ "
# define PROMPT_HEREDOC "> "

typedef struct s_minishell	t_minishell;

typedef struct s_cmd
{
	char			**cmd;
	char			**heredoc;
	char			*infile;
	char			*outfile;
	t_list			*skipped_in;
	t_list			*skipped_out;
	int				*whitespace;
	int 			append;
	int				inpipe;
	int				outpipe;
	struct s_cmd	*next;
}					t_cmd;


typedef struct s_blin
{
	char			*name;
	void			(*func)(t_minishell *, int, t_cmd *);
}					t_blin;

typedef struct s_mem
{
	char			*line;
	char			**tokens;
	char			***heredoc_tmp;
	int				current_heredoc;
	int				*ws_tmp;
	int				*ws_pipe_tmp;
	int				is_child;
}					t_mem;


typedef struct s_minishell
{
	char			**env;
	t_blin			*buildins;
	t_cmd			*cmd;
	t_mem			*tmp;
	int				exit_code;
}					t_minishell;

// shlvl.c
char		*increment_shlvl(const char *shlvl);
// MEMORY MANAGMENT
char		**array_init(void);
char		*allocate_string(size_t len, char *error);
char		*allocate_dup(char *dup, char *error);
char		**allocate_array(size_t len, char *error);
void		error_array_allocation(char **result, int i, char *error);
void		free_array(char **tokens);
void		free_heredoc_tmp(char ***heredoc_tmp);
void		free_cmd(t_cmd *cmd);
void		free_minishell(t_minishell *minishell);
void		exit_free(t_minishell *minishell, int exit_code);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int			*allocate_whitespaces(int count, char *error);
void		init_envp(t_minishell *minishell, char **env);
void		init_tmp(t_mem *tmp);
t_cmd		*init_cmd_node(int cmd_count);
void		init_minishell(t_minishell *minishell, char **env);
/*utils.c*/
void		*ft_realloc_exe(void *ptr, size_t size);
/*emulated comms*/
int			find_string_in_array(char **array, const char *str, size_t n);
void		execute_cd(t_minishell *minishell, int fd, t_cmd *cur);
void		execute_echo(t_minishell *minishell, int fd, t_cmd *cur);
void		execute_pwd(t_minishell *minishell, int fd, t_cmd *cur);
void		execute_export(t_minishell *minishell, int fd, t_cmd *cur);
void		execute_unset(t_minishell *minishell, int fd, t_cmd *cur);
void		execute_env(t_minishell *minishell, int fd, t_cmd *cur);
void		execute_exit(t_minishell *minishell, int fd, t_cmd *cur);
void 		execute_command(t_minishell *minishell, int fd, t_cmd *cur);
//exe
void		execute(t_minishell *minishell);
//signals
void		ft_signals(void);
//utils.c
char		*str_to_lower(char *str);
int			ft_isspace(char c);
//error
void		exit_fail(const char *exit_message);
void		not_found(t_minishell *minishell, char *cmd);
void		no_file(t_minishell *minishell, char *filename);
void		no_path_file(t_minishell *minishell, char *filename);
int			syntax_error(t_minishell *minishell, char *token);
void		arg_count_error(t_minishell *minishell, char *command);
void		exe_binary_error(t_minishell *minishell, char *path);
void		is_a_directory(t_minishell *minishell, char *path, char mode);
void		not_valid(t_minishell *minishell, char *cmd);
void		permission_denied(t_minishell *minishell, char *path);
void		numeric_error(t_minishell *minishell, char *cmd, char *arg);
//path.c
char		*get_path(t_minishell *minishell, char *cmd);

#endif