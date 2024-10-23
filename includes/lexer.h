/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:17:38 by aaleksee          #+#    #+#             */
/*   Updated: 2024/09/25 14:17:40 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

# define DELIMS "<>|"
# define QUOTES "'\""

int		lexer_main(t_minishell *minishell, char *line);
char	**tokenizator(int **ws_array, char *line);
int		quote_counter(t_minishell *minishell, char *line);
char	heredoc_check(char *line, char pipe_heredoc);
char	hanging_pipe_heredoc(char *line);
char	*extract_token(char **line, int i, int **ws_array, int *token_flag);
char	*getting_token(char *start, int len);
char	*getting_start(char **line, char *start, int *len);
void	delim_handler(char **line, int *len, int *in_token, char mode);
int		count_tokens(char *line);
int		set_quote(char **line, int *count, int in_token, char mode);
void	increment_len_line(char ***line, int **len);
int		is_delimiter(char *line);
void	set_token_flag(char *token, int *flag);
void	add_heredocs(t_minishell *minishell,
			char **tokens, size_t redirections);
char	**handle_heredoc(t_minishell *minishell, char **tokens);
char	**handle_pipe(t_minishell *minishell, char **tokens);
char	**pipe_heredoc_main(t_minishell *minishell, char *line);
char	**get_valid_tokens(void);
size_t	redirections_count(char **tokens);
int		incorrect_delimiter(char **delimiter);
char	*find_delimiter(char **tokens, size_t *i);
char	*read_heredoc_lines(char *delimiter);
char	**procees_heredoc_lines(char *delimiter);
void	add_line_to_heredoc(char ***heredoc_tokens, size_t *size,
			size_t *capacity, char *line);
char	*expand_question_mark_hd(t_minishell *minishell, char *token);
char	*substitute_hd(t_minishell *minishell, char *token, char *exp_token);
size_t	expanded_line_len_hd(t_minishell *minishell, char *token);
char	*expand_hd(t_minishell *minishell, char *token);
void	heredoc_expander(t_minishell *minishell, char **tokens);
char	**merge_tokens(char **tokens, char **new_tokens);
int		*merge_ws(int *ws, int *ws_pipe);
char	*expand_question_mark(t_minishell *minishell, char *token,
			char *current_quote);
char	*substitute(t_minishell *minishell, char *token,
			char *exp_token, char *current_quote);
char	*expand(t_minishell *minishell, char *token, int *comment_flag);
void	expander_main(t_minishell *minishell, char **tokens);
int		expand_to_env(t_minishell *minishell, char **cur_ptr, char cur_quote);
void	write_exit_code(char **result, char *exit_code, int *i, char **token);
void	set_current_quote(char *current_quote, char quote, char **token);
void	set_current_quote_question(char *current_quote, char quote);
void	delete_last_whitespace(t_cmd *cur);
void	delete_comment(char *token, char *current_quote, int *comment_flag);
size_t	expanded_line_len(t_minishell *minishell, char *token,
			char *current_quote);
size_t	exit_len(char *token, char *exit_code);
size_t	exit_len_hd(char *token, char *exit_code);
char	*find_env_value(char **env_array, char *var_name);
char	*env_var_copy(char **token);
char	*get_env_value(t_minishell *minishell, char **token);
int		hanging_tokens(char **tokens);
int		is_valid_token(char *token);
int		pipe_redirections_mistake(t_minishell *minishell, char **tokens);
int		validator_main(t_minishell *minishell, char ***tokens);
void	delimiter_counter(char **token, int *pipes, int *right_redirs,
			int *left_redirs);
int		tokens_counter(char **tokens);
int		should_merge(char **tokens, int i, int *ws_tmp);
void	merge_token(char **tokens, int *ws_tmp, int i);
int		handle_merge(char **tokens, int *ws_tmp, int i, int j);
void	merger_main(t_minishell *minishell, char **tokens);
void	process_token(t_minishell **minishell, t_cmd *current, char *token,
			int *i);
void	parser_main(t_minishell **minishell, char ***tokens);
void	process_node(t_cmd **current, t_cmd **cmd_list,
			char *token, size_t ws_count);
void	add_command(t_minishell **minishell, t_cmd *current,
			char *token, int *i);
int		is_pipe(char *token);
int		is_redirection(char *token);
void	handle_redirections(t_cmd *current, char *delimiter, char *file);
size_t	array_len(char **array);
size_t	int_array_len(int *array);
char	**del_empty(t_minishell *minishell, char **tokens);
void	print_visible(char *str);
void	print_list_state_v(t_minishell *minishell, char *name);
void	print_tokens_state_v(t_minishell *minishell, char **tokens,
			char *name, char mode);

#endif