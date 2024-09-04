#include "lexer.h"
#include "minishell.h"

void	assign_pipes(t_minishell *minishell, char *delimiter)
{
	t_cmd	*current;

	current = minishell->cmd;
	if (ft_strncmp(delimiter, "|", ft_strlen(delimiter)) == 0)
	{
		current->outfile = 1;
		current->next->infile = 1;
	}
	else if (ft_strncmp(delimiter, ">", ft_strlen(delimiter)) == 0)
		current->next->outfile = 1;
	else if (ft_strncmp(delimiter, ">>", ft_strlen(delimiter)) == 0)
		current->outfile = 2;
	else if (ft_strncmp(delimiter, "<", ft_strlen(delimiter)) == 0)
	{
		current->infile = 1;
		// maybe there whould be fd ?
	}
	else if (ft_strncmp(delimiter, "<<", ft_strlen(delimiter)) == 0)
		current->infile = 2;
}

void	init_command(t_minishell *minishell)
{
	minishell->cmd->infile = 0;
	minishell->cmd->outfile = 0;
	minishell->cmd = NULL;
}
