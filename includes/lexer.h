#ifndef LEXER_H
# define LEXER_H
# include "minishell.h" 
# define DELIMS "<>|"
# define QUOTES "'\""

void	lexer_main(t_minishell *minishell, char *line);
char	*quote_counter(char *line);
char	**tokenizator(char *line);

char	*extract_token(char **line);
char	*getting_start(char **line, char *start, int *len);
char	*getting_token(char *start, int len);

char	*find_end_quote(char *line, int *count);
int		find_quotation_len(char *line);
int		count_tokens(char *line);
int		is_delimiter(char *line);

char	**expander_main(t_minishell *minishell, char **tokens);
void	substitute_env(t_minishell *minishell, char **token, char **result,
			int *i);
char	*expand_quoted_line(t_minishell *minishell, char *token, size_t len);
char	*expand_dollar_line(t_minishell *minishell, char *token, size_t len);

char	*env_var_copy(char **token);
char	set_quote(char c, int *in_quote);
size_t	expanded_env_var_len(char *line);
size_t	expanded_line_len(t_minishell *minishell, char *token);

char	*allocate_env_value(char *value);
char	*find_env_value(t_list *env_list, char *var_name);
char	*get_env_value(t_minishell *minishell, char **token);
size_t	env_value_len(t_minishell *minishell, char **token);

void	parser_main(t_minishell *minishell, char **tokens);
int		process_command(t_minishell *minishell, char **tokens, int start,
			int end);
void	process_tokens(t_minishell *minishell, char **tokens);
void	delimiter_parser(t_minishell *minishell);

char	**copy_tokens(char **tokens, int start, int end);
int		is_delimiter_parser(char *token);
void	free_tokens(char **tokens);

void	init_command(t_minishell *minishell);
void	assign_pipes(t_minishell *minishell, char *delimiter);

t_cmd	*ft_mini_lstnew(char **content);
void	ft_lstadd_mini_back(t_cmd **lst, t_cmd *new);

char	**array_init(void);

void	print_list_state(t_minishell *minishell);

#endif