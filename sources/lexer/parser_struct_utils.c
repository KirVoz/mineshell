#include "lexer.h"
#include "minishell.h"

void	assign_pipes(char *delimiter, t_cmd *current)
{
	if (ft_strncmp(delimiter, "|", ft_strlen(delimiter)) == 0)
	{
		current->outfile = 1;
		if (current->next)
			current->next->infile = 1;
	}
	else if (ft_strncmp(delimiter, ">", ft_strlen(delimiter)) == 0)
	{
		current->outfile = 2;
		if (current->next)
			current->next->infile = 2;
	}
	else if (ft_strncmp(delimiter, ">>", ft_strlen(delimiter)) == 0)
		current->outfile = 3;
	else if (ft_strncmp(delimiter, "<", ft_strlen(delimiter)) == 0)
	
	{
		current->infile = 4;
		// maybe there should be fd or pid?
	}
	else if (ft_strncmp(delimiter, "<<", ft_strlen(delimiter)) == 0)
		current->infile = 5;
	else
		return ;
}

void	init_command(t_minishell *minishell)
{
	minishell->cmd->infile = 0;
	minishell->cmd->outfile = 0;
	minishell->cmd = NULL;
}
