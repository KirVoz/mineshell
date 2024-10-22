/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:16:04 by aaleksee          #+#    #+#             */
/*   Updated: 2024/10/13 22:16:06 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

# define PROMPT "minishell$ "
# define PROMPT_HEREDOC "> "

volatile sig_atomic_t		g_child;

typedef struct s_minishell	t_minishell;

typedef struct s_cmd
{
	char			**cmd;
	char			**heredoc;
	int				*whitespace;
	t_list			*files;
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
	char			*path;
	int				**pipes;
}					t_minishell;

typedef struct s_in_out
{
	int				in;
	int				out;
}					t_in_out;
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
t_cmd		*init_cmd_node(size_t ws_count);
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
void		execute_command(t_minishell *minishell, int fd, t_cmd *cur);
//exe
t_blin		*get_commands(void);
void		execute(t_minishell *minishell);
int			solo_builtin(char *cmd);
int			is_builtin(char *cmd);
void		free_pipes(int **pipes, int num_cmd);
void		write_heredoc_to_fd(t_cmd *cmd, int fd);
void		heredoc_fd(t_cmd *cmd);
void		open_file(t_minishell *minishell, const char *filename,
				int perm_or_no_file);
void		close_pipes(int **pipes, int num_cmd);
int			path_present(t_minishell *minishell);
int			file_dir_check(char *cmd);
void		handle_file_dir(t_minishell *minishell, char **cmd);
int			count_commands(t_cmd *cmd);
int			**setup_pipes(int num_cmd);
void		redirects(t_minishell *minishell, t_cmd *current, int i,
				int num_cmd);
void		handle_hd(t_cmd *current, int *last_input_fd);
void		handle_output_file(t_minishell *minishell, t_list *tmp,
				int *last_output_fd, int flags);
void		handle_input_file(t_minishell *minishell, t_list *tmp,
				int *last_input_fd);
void		update_underscore_variable(t_minishell *minishell);
//export
void		declare_env_var(t_minishell *minishell, int fd);
int			ft_check_valid_simbol(char *new_var);
int			ft_check_valid_identifier(char *new_var);
int			validation_check(t_minishell *minishell, t_cmd *cur,
				int fd, int *i);
char		*construct_declare(char *env_var);
//signals
void		ft_signals(void);
void		ft_default_signals(void);
//utils.c
char		*str_to_lower(char *str);
int			ft_isspace(char c);
//error
void		exit_fail(const char *exit_message);
char		*construct_error(char *arg1, char *arg2, char *arg3, char mode);
void		not_found(t_minishell *minishell, char *cmd);
void		no_file(t_minishell *minishell, char *filename);
void		no_path_file(t_minishell *minishell, char *filename);
int			syntax_error(t_minishell *minishell, char *token);
void		arg_count_error(t_minishell *minishell, char *command);
void		exe_binary_error(t_minishell *minishell, char *path);
void		is_a_directory(t_minishell *minishell, char *path, char mode);
void		not_valid(t_minishell *minishell, char *cmd, int exit_code);
void		permission_denied(t_minishell *minishell,
				char *path, int redirs_or_file);
void		numeric_error(t_minishell *minishell, char *cmd, char *arg);
void		deleted_dir(t_minishell *minishell);
void		handle_incorrect_arguments(t_minishell *minishell, char *av);
//path.c
char		*get_path(t_minishell *minishell, char *cmd);
void		ft_free_exe_free(t_minishell *minishell, t_cmd *current);

#endif
