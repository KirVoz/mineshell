#include "lexer.h"
#include "minishell.h"

void	process_token(t_cmd *current, char *token, char *next_token, int *i)
{
	if (is_redirection(token))
	{
		handle_redirections(current, token, next_token);
		*i += 2;
	}
	else
	{
		add_command(current, token);
		(*i)++;
	}
}

void	parser_main(t_minishell **minishell, char ***tokens)
{
	t_cmd	*current;
	t_cmd	*cmd_list;
	int		i;

	current = NULL;
	cmd_list = NULL;
	i = 0;
	while ((*tokens)[i])
	{
		process_node(&current, &cmd_list, (*tokens)[i]);
		if (if_pipe((*tokens)[i]))
		{
			i++;
			continue ;
		}
		process_token(current, (*tokens)[i], (*tokens)[i + 1], &i);
	}
	(*minishell)->cmd = cmd_list;
	free_tokens(*tokens);
	*tokens = NULL; 
}
