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

// LEXER //del
int		lexer_main(t_minishell *minishell, char *line);
// char	**tokenizator(char *line);
char	**tokenizator(int **ws_array, char *line);
char	*quote_counter(char *line);
char	hanging_pipe_heredoc(char *line);
// void	delete_whitespace_before_token(char **token);

// TOKENIZATOR //del
// char	*extract_token(char **line, int i, int *token_flag);
char	*extract_token(char **line, int i, int **ws_array, int *token_flag);
char	*getting_token(char *start, int len);
char	*getting_start(char **line, char *start, int *len);
void	redirection_handle(char **line, int *count, int *in_token);
int		count_tokens(char *line);
char	*find_end_quote(char *line, int *count);
char	*find_end_quote_len(char *line, int *len);
int		find_quotation_len(char *line);
int		is_delimiter(char *line);
void	set_token_flag(char *token, int *flag);
// PIPE_HEREDOC //del
void	add_heredocs(t_minishell *minishell,
			char **tokens, size_t redirections);
char	**handle_heredoc(t_minishell *minishell, char **tokens);
char	**handle_pipe(t_minishell *minishell, char **tokens);
char	**pipe_heredoc_main(t_minishell *minishell, char *line);
// PIPE_HEREDOC_UTILS //del
char	**get_valid_tokens(void);
size_t	redirections_count(char **tokens);
int		incorrect_delimiter(char **delimiter);
// HEREDOC_UTILS //del
char	*find_delimiter(char **tokens, size_t *i);
char	*read_heredoc_lines(char *delimiter);
char	**procees_heredoc_lines(char *delimiter);
void	add_line_to_heredoc(char ***heredoc_tokens, size_t *size,
			size_t *capacity, char *line);
char	**merge_tokens(char **tokens, char **new_tokens);
char	*expand_question_mark_hd(t_minishell *minishell, char *token);
char	*substitute_hd(t_minishell *minishell, char *token, char *exp_token);
size_t	expanded_line_len_hd(t_minishell *minishell, char *token);
char	*expand_hd(t_minishell *minishell, char *token);
void	heredoc_expander(t_minishell *minishell, char **tokens);
// EXPANDER //del
char	*expand_question_mark(t_minishell *minishell, char *token,
			char *current_quote);
char	*substitute(t_minishell *minishell, char *token,
			char *exp_token, char *current_quote);
char	*expand(t_minishell *minishell, char *token, int i);
void	delete_last_whitespace(t_cmd *cur);
void	expander_main(t_minishell *minishell, char **tokens);
int		expand_to_env(t_minishell *minishell, char **cur_ptr, char cur_quote);
void	write_exit_code(char **result, char *exit_code, int *i, char **token);
void	set_current_quote(char *current_quote, char quote, char **token);
size_t	expanded_line_len(t_minishell *minishell, char *token,
			char *current_quote);
size_t	exit_len(char *token, char *exit_code);
size_t	exit_len_hd(char *token, char *exit_code);
char	*find_env_value(char **env_array, char *var_name);
char	*env_var_copy(char **token);
char	*get_env_value(t_minishell *minishell, char **token);
// void	processing_quoted_line(t_minishell *minishell, char **token,
// 			char *result, char *current_quote);
// char	*expand_quoted_line(t_minishell *minishell, char *token, size_t len);
// char	*expand_dollar_line(t_minishell *minishell, char *token, size_t len);
// size_t	exit_len_hc(char *token, char *exit_code);
// char	*expand_question_mark(t_minishell *minishell, char *token);
// void	expander_main(t_minishell *minishell, char **tokens);
// size_t	strlcpy_eq(char *dst, const char *src, size_t dstsize);
// char	*allocate_dup(char *dup, char *error);
// char	set_quote(char c, int *in_quote);
// void	write_exit_code(char **result, char *exit_code, int *i);
// void	digit_env_var_substitute(char **token, char **result, int *i);
// size_t	expanded_line_len(t_minishell *minishell, char *token);
// size_t	env_value_len(t_minishell *minishell, char **token);
// size_t	digit_env_var_len(char **token);
// size_t	additional_len(char *token);
// size_t	expanded_env_var_len(char *line);
// size_t	count_to_dollar(char **line);
// size_t	exit_len(char *token, char *exit_code);
// char	*find_env_value(char **env_array, char *var_name);
// char	*get_env_value(t_minishell *minishell, char **token);
// char	*env_var_copy(char **token);
// void	substitute_env(t_minishell *minishell, char **token, char **result,
// 			int *i);
// VALIDATOR //del
int		hanging_tokens(char **tokens);
int		is_valid_token(char *token);
int		pipe_redirections_mistake(t_minishell *minishell, char **tokens);
int		validator_main(t_minishell *minishell, char ***tokens);
void	delimiter_counter(char **token, int *pipes, int *right_redirs,
			int *left_redirs);
int		tokens_counter(char **tokens);
// PARSER //del
void	process_token(t_minishell **minishell, t_cmd *current, char *token,
			int *i);
void	parser_main(t_minishell **minishell, char ***tokens);
void	process_node(t_cmd **current, t_cmd **cmd_list,
			char *token, int cmd_count);
// void	add_command(t_cmd *current, char *token);
void	add_command(t_minishell **minishell, t_cmd *current,
			char *token, int *i);
int		is_pipe(char *token);
int		is_redirection(char *token);
void	store_skipped_infiles(t_cmd **current);
void	store_skipped_outfiles(t_cmd **current);
void	handle_redirections(t_cmd *current, char *delimiter, char *file);
// MEMORY_MANAGEMENT //del
char	**array_init(void);
char	*allocate_string(size_t len, char *error);
char	*allocate_dup(char *dup, char *error);
char	**allocate_array(size_t len, char *error);
void	error_array_allocation(char **result, int i, char *error);
void	free_tokens(char **tokens);
void	free_heredoc_tmp(char ***heredoc_tmp);
void	free_cmd(t_cmd *cmd);
void	free_minishell(t_minishell *minishell);
void	exit_free(t_minishell *minishell, int exit_code);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int		*allocate_whitespaces(int count, char *error);
// GENERAL_UTILS //del
size_t	array_len(char **array);
// DEBUG //del
void	print_visible(char *str);
void	print_list_state_v(t_minishell *minishell, char *name);
void	print_tokens_state_v(t_minishell *minishell, char **tokens,
			char *name, char mode);
void	print_list_state(t_minishell *minishell, char *name);
void	print_tokens_state(char **tokens, char *name);

#endif
