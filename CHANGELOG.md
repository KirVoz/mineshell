## CHANGELOG

### 29.08 Alex
General:
- Added **libft**.
- Added sub-directories.
- Added header for lexer and tokenizator - lexer.h.
- Added tokenizator.c file with the helper functions for tokenizator.
- Added Makefile. Working on compilation readline with our Makefile.  
For now here're two variables: INCFLAGS and LDFLAGS for your own path.
- Excluded pipes.c from Makefile since it doesn't work.
- Voided av, env in main and env in init_minishell.

Functions:
- Renamed lex\_line to lexer\_main.
- Added int	quote_counter(char *line) for checking if there's a syntax error on the stage of tokenisation.
- Added char \*\*tokenizator(const char \*line) and helper functions. It results in array of strings where every token takes single string except for quoted:  
cat -e | echo "  Hi ", hi"     'a' someone" > b.txt  < a.txt
{"cat", "-e", "|", "echo", "  Hi ", hi"     'a' someone", NULL}

Problems:
- Tokenisation doesn't truncate leading white-spaces and could lost tokens if any present.




### 29.08 Kirill

General:
- School PC have readlinelib issues, need to improve MAKEFILE
- Add conections in minishell.h <-> lexer.h
- lexer_main "tokenss" must be in struct?
- char **envp can be divided to char * and added in t_list format struct
- add t_minishell to lexer_main()

Problems:
- readline lib
- tokenization logic

Suggestions:
- maybe realization with lists will be great in all cases. that will improve accessibility for growing amount of data

### 31.08 Alex
Functions:
- Fixed	quote_counter, now it correctly counts amount of quotation marks
- Fixed incorrect tokenizator's behavior with leading white-spaces
- Added char	*find\_end\_quote(char *line, int *count) function for correct search of end-quotes and made it take into account if nested quotation marks are separate arguments or part of the outer quotes
- Changed count\_tokens function so it's correctly counts all tokens  
Now every function is under 25 lines. Wo-ho!



### 31.08

General:
- Add envp initialization (add some sort of env comand in comands.c)
- modify .h to optimize blin struct

### 10.09

Add: redirects
- я добавил в стракт смд инт аппенд который должен добавлятся если есть >> так же оставляя infile (реализовал через тернарный оператор открытия файла)
- стоит провести тесты 
- так же добавленно коректное исполнение одиночных функций через енв
- билдины пока что не работают корректно 
