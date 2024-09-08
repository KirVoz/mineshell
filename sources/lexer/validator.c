#include "lexer.h"
#include "minishell.h"

// int	pipe_redirections_mistake(t_minishell *minishell, int pipes, 
// 	int left_redir, int right_redir)
// {
// 	if (pipes > 1)
// 		return(syntax_error(minishell, "|"));
// 	else if ()
// }

void	delimiter_counter(char **token, int *pipes,
			int *right_redirs, int *left_redirs)
{
	*pipes = 0;
	*right_redirs = 0;
	*left_redirs = 0;
	while (*token && ft_strchr(DELIMS, **token))
	{
		if (**token == '|')
			(*pipes)++;
		else if (**token == '>')
			(*right_redirs)++;
		else if (**token == '<')
			(*left_redirs)++;
		token++;
	}
}
int	pipe_redirections_unification(t_minishell *minishell, char **tokens)
{
	int	pipes;
	int	right_redirs;
	int	left_redirs;

	while (*tokens)
	{
		delimiter_counter(tokens, &pipes, &right_redirs, &left_redirs);
		printf("pipe redir %d %d %d\n", pipes, right_redirs, left_redirs);
		if (pipes > 1)
			return(syntax_error(minishell, "|"));
		else if (right_redirs == 3)
			return(syntax_error(minishell, ">"));
		else if (right_redirs > 3)
			return(syntax_error(minishell, ">>"));
		else if (left_redirs == 3)
			return(syntax_error(minishell, "<"));
		else if (left_redirs > 4)
			return(syntax_error(minishell, "<<"));
		
		tokens++;
	}
	return (1);
}

int	validator_main(t_minishell *minishell, char **tokens)
{
	char	**cp_tokens;

	cp_tokens = tokens;
	pipe_redirections_unification(minishell, cp_tokens);
	return (1);
}
