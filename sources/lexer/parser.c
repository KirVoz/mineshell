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

char	**alloc_empty_cmd(void)
{
	char	**empty_cmd;

	empty_cmd = NULL;
	empty_cmd = (char **)malloc(2 * sizeof(char *));
	if (!empty_cmd)
		exit_fail("Failed to allocate memory for command array");
	empty_cmd[0] = ft_strdup("\0");
	if (!empty_cmd[0])
	{
		free(empty_cmd);
		exit_fail("Failed to allocate memory for command");
	}
	return (empty_cmd);
}


void	handle_empty_cmd(t_cmd **current)
{
	// t_cmd	*command_node;
	// t_cmd	*last;

	if (!(*current)->cmd)
		(*current)->cmd = alloc_empty_cmd();
	// command_node = create_empty_node();
	// command_node->cmd = alloc_empty_cmd();
	// last = *current;
	// while (last->next)
	// 	last = last->next;
	// last->next = command_node;
	// *current = command_node;
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
