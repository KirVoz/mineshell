#ifndef LEXER_H
# define LEXER_H

# include "minishell.h" 

# define DELIMS "<>|"
# define QUOTES "'\""

typedef struct s_quotes
{
	char	outer_q;
	char	other_q;
	int		is_literal;
	int		len;
}			t_quotes;

void	lexer_main(t_minishell *minishell, char *line);
int		quote_counter(char *line);
char	**tokenizator(char *line);

char	*extract_token(char **line);
char	*getting_start(char **line, char *start, int *len);
char	*getting_token(char *start, int len);

char	*find_end_quote(char *line, int *count);
int		find_quotation_len(char *line);
int		count_tokens(char *line);
int		is_delimiter(char *line);

char	**expander(t_minishell *minishell, char **tokens);

void	parser(t_minishell *minishell, char **tokens);
#endif