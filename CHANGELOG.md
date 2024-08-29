## CHANGELOG

### 29.08
General:
- Added **libft**.
- Added subdirectories.
- Added header for lexer and tokenisator - lexer.h.
- Added tokenisator.c file with the helper functions for tokenisator.
- Added Makefile. Working on compilation readline with our makefile.  
For now here're two variables: INCFLAGS and LDFLAGS for your own path.
- Excluded pipes.c from Makefile since it doesn't work.
- Voided av, env in main and env in init_minishell.

Functions:
- Renamed lex\_line to lexer\_main.
- Added int	quote_counter(char *line) for checking if there's a syntax error on the stage of tokenisation.
- Added char \*\*tokenisator(const char \*line) and helper functions. It results in array of strings where every token takes single string except for quoted:  
cat -e | echo "  Hi ", hi"     'a' someone"  
{"cat", "-e", "|", "echo", "  Hi ", hi"     'a' someone", NULL}

Problems:
- Tokenisation doesn't truncate leading whitespaces and could lost tokens if any present.