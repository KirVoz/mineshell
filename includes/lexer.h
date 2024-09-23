#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# define DELIMS "<>|"
# define QUOTES "'\""
# define VALID_TOKENS {"|", "<", ">", "<<", ">>", NULL}

// DEBUG //del
void	print_list_state(t_minishell *minishell, char *name);
void	print_tokens_state(char **tokens, char *name);

// LEXER //del
int		lexer_main(t_minishell *minishell, char *line);
char	**tokenizator(char *line);

// LEXER_UTILS //del
char	*quote_counter(char *line);
char	hanging_pipe_heredoc(char *line);

// TOKENIZATOR //del
char	*extract_token(char **line);
char	*getting_start(char **line, char *start, int *len);
char	*getting_token(char *start, int len);

// TOKENIZATOR_UTILS //del
char	*find_end_quote(char *line, int *count);
int		find_quotation_len(char *line);
int		count_tokens(char *line);
int		is_delimiter(char *line);

// PIPE_HEREDOC //del
char	**pipe_heredoc_main(t_minishell *minishell, char *line);
char	**handle_heredoc(t_minishell *minishell, char **tokens);
void	add_heredocs(t_minishell *minishell, char **tokens, size_t redirections);

// PIPE_HEREDOC_UTILS //del
size_t	redirections_count(char **tokens);

// HEREDOC_UTILS //del
char	*find_delimiter(char **tokens, size_t *i);
char	**read_heredoc_lines(char *delimiter);
void	add_line_to_heredoc(char ***heredoc_tokens, size_t *size,
			size_t *capacity, char *line);

// EXPANDER //del
void	substitute_env(t_minishell *minishell, char **token, char **result,
			int *i);
char	*expand_quoted_line(t_minishell *minishell, char *token, size_t len);
char	*expand_dollar_line(t_minishell *minishell, char *token, size_t len);
void	expander_main(t_minishell *minishell, char **tokens);

// EXPANDER_UTILS //del
size_t	strlcpy_eq(char *dst, const char *src, size_t dstsize);
char	*allocate_env_value(char *value);
char	set_quote(char c, int *in_quote);
int		dollar_special_case(char **token);

// EXPANDER_LEN_UTILS //del
size_t	expanded_line_len(t_minishell *minishell, char *token);
size_t	expanded_env_var_len(char *line);
size_t	env_value_len(t_minishell *minishell, char **token);
size_t	digit_env_var_len(char **token);
size_t	additional_len(char *token);

// EXPANDER_ENV_UTILS //del
char	*find_env_value(char **env_array, char *var_name);
char	*get_env_value(t_minishell *minishell, char **token);
char	*env_var_copy(char **token);
void	digit_env_var_substitute(char **token, char **result, int *i);

// VALIDATOR //del
int		pipe_redirections_mistake(t_minishell *minishell, char **tokens);
int		redirections_unification_required(char **tokens);
int		hanging_redirections(char **tokens);
int		validator_main(t_minishell *minishell, char ***tokens);

// VALIDATOR_UTILS //del
void	delimiter_counter(char **token, int *pipes, int *right_redirs,
			int *left_redirs);
int		tokens_counter(char **tokens);
char	**tokens_realloc(char ***tokens);

// PARSER //del
void	process_token(t_minishell **minishell, t_cmd *current, char *token,
			char *next_token, int *i);
void	parser_main(t_minishell **minishell, char ***tokens);

// PARSER_LIST_UTILS //del
void	process_node(t_cmd **current, t_cmd **cmd_list, char *token);
void	add_command(t_cmd *current, char *token);

// PARSER_UTILS //del
int		if_pipe(char *token);
int		is_redirection(char *token);
void	store_skipped_infiles(t_cmd **current);
void	store_skipped_outfiles(t_cmd **current);
void	handle_redirections(t_cmd *current, char *delimiter, char *file);

// MEMORY_MANAGEMENT //del
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	**array_init(void);
void	free_tokens(char **tokens);
void	free_cmd(t_cmd *cmd);
void	free_heredoc_tmp(char ***heredoc_tmp);
void	free_minishell(t_minishell *minishell);
void	exit_free(t_minishell *minishell, int exit_code);
char	*allocate_string(size_t len, char *error);
char	**allocate_array(size_t len, char *error);
void	error_array_allocation(char **result, int i);

// GENERAL_UTILS //del
size_t	array_len(char **array);

#endif