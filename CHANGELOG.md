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




### 29.08

General:
- School PC have readlinelib issues, need to improve MAKEFILE
- Add conections in minishell.h <-> lexer.h
- lexer_main "tokenss" must be in struct?
- char **envp can be divided to char * and added in t_list format struct
- add t_minishell to lexer_main()

Problems:
- readline lib
- tokinization logic

Sugestions:
- tokinization may be 2lvl
 - ls | ls ; cd ; echo 123 
       /      |      \
	  /       |       \
	ls | ls   |        \
	|    	 cd       echo 123
   / \					/   \
ls    ls              echo   123
and so on

- maybe realization with lists will be great in all cases. that will improve accessability for growing amount of data



### 31.08

General:
- Add envp initialization (add some sort of env comand in comands.c)
- modify .h to optimize blin struct

