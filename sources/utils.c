#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->cmd != NULL)
	{
		for (int i = 0; cmd->cmd[i] != NULL; i++)
			free(cmd->cmd[i]);
		free(cmd->cmd);
	}
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->skipped_in);
	free(cmd->skipped_out);
	free_cmd(cmd->next);
	free(cmd);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell == NULL)
		return ;
	free_cmd(minishell->cmd);
}