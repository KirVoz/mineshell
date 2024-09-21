#include "lexer.h"
#include "minishell.h"

void	process_token(t_minishell **minishell, t_cmd *current,
			char *token, char *next_token, int *i)
{
	if (is_redirection(token))
	{
		handle_redirections(current, token, next_token);
		if (ft_strncmp(token, "<<", 2) == 0)
			current->heredoc
				= (*minishell)->heredoc_tmp[(*minishell)->current_heredoc++];
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
		process_token(minishell, current, (*tokens)[i], (*tokens)[i + 1], &i);
		if (!current->cmd)
			current->cmd = array_init();
	}
	(*minishell)->cmd = cmd_list;
	free_tokens(*tokens);
	*tokens = NULL; 
}
