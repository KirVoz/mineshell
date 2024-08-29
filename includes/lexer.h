#ifndef LEXER_H
# define LEXER_H

# include "minishell.h" 

# define DELIMS "<>|"
# define QUOTES "'\""

void	lexer_main(t_minishell *minishell, char *line);
int		quote_counter(char *line);
char	**tokenisator(const char *line);

int 	count_tokens(const char *line);
char 	*extract_token(const char **line);
char 	*getting_start(const char **line, char *quote, int *len);
char 	*getting_token(const char *start, int len);
int		is_delimiter(const char *line);

#endif