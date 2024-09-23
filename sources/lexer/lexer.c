#include "lexer.h"
#include "minishell.h"

char	**tokenizator(char *line)
{
	int		i;
	int		token_count;
	char	**result;

	i = 0;
	token_count = count_tokens(line);
	result = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!result)
		exit_fail("Failed to allocate memory for tokens in tokenizator");
	while (*line && *line == ' ')
		line++;
	while (i < token_count)
	{
		result[i] = extract_token(&line);
		if (!result[i])
			error_array_allocation(result, i);
		i++;
	}
	result[token_count] = NULL;
	return (result);
}

int	lexer_main(t_minishell *minishell, char *line)
{
	if (quote_counter(line))
		return (syntax_quote_error(minishell, quote_counter(line)));
	if (hanging_pipe_heredoc(line))
		minishell->tmp->tokens = pipe_heredoc_main(minishell, line);
	else
		minishell->tmp->tokens = tokenizator(line);
	// print_tokens_state(minishell->tmp->tokens, "after tokenizator, before expander"); //del
	expander_main(minishell, minishell->tmp->tokens);
	// print_tokens_state(minishell->tmp->tokens, "after expander, before validator"); //del
	if (!validator_main(minishell, &minishell->tmp->tokens))
	{
		free_minishell(minishell);
		return (0);
	}
	// print_tokens_state(minishell->tmp->tokens, "after validator"); //del
	parser_main(&minishell, &minishell->tmp->tokens);
	// print_list_state(minishell, "after parser"); //del
	return (1);
}
