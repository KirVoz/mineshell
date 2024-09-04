#include "lexer.h"
#include "minishell.h"

int	process_command(t_minishell *minishell, char **tokens, int start, int end)
{
	char	**cmd_tokens;
	t_cmd	*new_cmd;

	cmd_tokens = copy_tokens(tokens, start, end);
	if (!cmd_tokens)
		return (0);
	new_cmd = ft_mini_lstnew(cmd_tokens);
	if (!new_cmd)
	{
		free_tokens(cmd_tokens);
		return (0);
	}
	ft_lstadd_mini_back(&(minishell->cmd), new_cmd);
	return (1);
}

void	process_tokens(t_minishell *minishell, char **tokens)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (tokens[i])
	{
		if (is_delimiter_parser(tokens[i]) || tokens[i + 1] == NULL)
		{
			if (!process_command(minishell, tokens, start, i))
				exit_fail("Failed to process commands");
			start = i + 1;
		}
		i++;
	}
}

void	delimiter_parser(t_minishell *minishell)
{
	t_cmd	*current;
	char	**cmd_ptr;
	char	*delimiter;

	current = minishell->cmd;
	while (current != NULL)
	{
		cmd_ptr = current->cmd;
		while (*cmd_ptr)
		{
			if (is_delimiter_parser(*cmd_ptr))
			{
				delimiter = ft_strdup(*cmd_ptr);
				free(*cmd_ptr);
				*cmd_ptr = NULL;
				assign_pipes(minishell, delimiter);
				free(delimiter);
			}
			cmd_ptr++;
		}
		current = current->next;
	}
}

void	parser_main(t_minishell *minishell, char **tokens)
{
	char	**empty_cmd;

	init_command(minishell);
	process_tokens(minishell, tokens);
	delimiter_parser(minishell);
	if (minishell->cmd == NULL)
	{
		empty_cmd = (char **)malloc(2 * sizeof(char *));
		if (!empty_cmd)
			exit_fail("Failed to allocate memory for empty command");
		empty_cmd[0] = ft_strdup("");
		empty_cmd[1] = NULL;
		minishell->cmd = ft_mini_lstnew(empty_cmd);
		if (!minishell->cmd)
			exit_fail("Failed to create empty command node");
	}
}
