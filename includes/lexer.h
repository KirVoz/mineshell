#ifndef LEXER_H
# define LEXER_H
# include "minishell.h" 
# define DELIMS "<>|"
# define QUOTES "'\""

void	print_list_state(t_minishell *minishell, char *name);
void	print_tokens_state(char **tokens, char *name);

int		lexer_main(t_minishell *minishell, char *line);
char	*quote_counter(char *line);
char	**tokenizator(char *line);

char	*extract_token(char **line);
char	*getting_start(char **line, char *start, int *len);
char	*getting_token(char *start, int len);

char	*find_end_quote(char *line, int *count);
int		find_quotation_len(char *line);
int		count_tokens(char *line);
int		is_delimiter(char *line);

void	expander_main(t_minishell *minishell, char **tokens);
void	substitute_env(t_minishell *minishell, char **token, char **result,
			int *i);
char	*expand_quoted_line(t_minishell *minishell, char *token, size_t len);
char	*expand_dollar_line(t_minishell *minishell, char *token, size_t len);

char	*env_var_copy(char **token);
char	set_quote(char c, int *in_quote);
size_t	expanded_env_var_len(char *line);
size_t	expanded_line_len(t_minishell *minishell, char *token);
int		dollar_special_case(char *token);

char	*allocate_env_value(char *value);
char	*find_env_value(t_list *env_list, char *var_name);
char	*get_env_value(t_minishell *minishell, char **token);
size_t	env_value_len(t_minishell *minishell, char **token);

int		validator_main(t_minishell *minishell, char ***tokens);
int		redirections_unification(char **tokens);
int		pipe_redirections_mistake(t_minishell *minishell, char **tokens);

void	delimiter_counter(char **token, int *pipes, int *right_redirs,
			int *left_redirs);
int		tokens_counter(char **tokens);
char	**tokens_realloc(char **tokens);
int		redirections_check(char ***tokens);

void	parser_main(t_minishell **minishell, char ***tokens);
void	process_token(t_cmd *current, char *token, char *next_token, int *i);

t_cmd	*create_empty_node(void);
void	process_node(t_cmd **current, t_cmd **cmd_list, char *token);
void	add_command(t_cmd *current, char *token);

int		if_pipe(char *token);
int		is_redirection(char *token);
void	handle_redirections(t_cmd *current, char *delimiter, char *file);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	free_tokens(char **tokens);
char	**array_init(void);

// pipe_heredoc // del
char	**pipe_heredoc_main(char *line);
char	**handle_heredoc(char *line);

size_t	array_len(char **array);
size_t	redirections_count(char **tokens);
char	*strdup_nl(const char *s1);

char	*find_delimeter(char **tokens, size_t *i);
char	**read_heredoc_lines(char *delimiter);
void	add_line_to_heredoc(char ***heredoc_tokens, size_t *size,
			size_t *capacity, char *line);
char	**merge_tokens(char **tokens, char ***heredoc_tokens, size_t *i);

char	hanging_pipe_heredoc(char *line);

void	handle_empty_cmd(t_cmd **current);

#endif