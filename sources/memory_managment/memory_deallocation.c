#include "lexer.h"
#include "minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
}

void	free_heredoc_tmp(char ***heredoc_tmp)
{
	int	i;

	i = 0;
	while (heredoc_tmp[i])
	{
		free_tokens(heredoc_tmp[i]);
		i++;
	}
	free(heredoc_tmp);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	free(cmd->infile);
	free(cmd->outfile);
	free_tokens(cmd->cmd);
	ft_lstclear(&cmd->skipped_in, free);
	ft_lstclear(&cmd->skipped_out, free);
	cmd->append = 0;
	cmd->inpipe = 0;
	cmd->outpipe = 0;
	free_cmd(cmd->next);
	free(cmd);
}

void	free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->tmp->tokens)
	{
		free_tokens(minishell->tmp->tokens);
		minishell->tmp->tokens = NULL;
	}
	if (minishell->tmp->heredoc_tmp)
	{
		free_heredoc_tmp(minishell->tmp->heredoc_tmp);
		minishell->tmp->heredoc_tmp = NULL;
	}
	minishell->tmp->current_heredoc = 0;
	if (minishell->cmd)
	{
		free_cmd(minishell->cmd);
		minishell->cmd = NULL;
	}
	if (minishell->tmp->line)
	{
		free(minishell->tmp->line);
		minishell->tmp->line = NULL;
	}
}

void	exit_free(t_minishell *minishell, int exit_code)
{
	free_minishell(minishell);
	free(minishell->tmp);
	free_tokens(minishell->env->envp_var);
	free(minishell->env);
	exit(exit_code);
}
