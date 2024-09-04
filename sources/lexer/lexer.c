#include "lexer.h"
#include "minishell.h"

int	quote_counter(char *line)
{
	int		double_q;
	int		single_q;
	char	*line_cpy;

	double_q = 0;
	single_q = 0;
	line_cpy = line;
	while (*line_cpy)
	{
		if (ft_strchr("\"", *line_cpy))
			double_q++;
		else if (ft_strchr("\'", *line_cpy))
			single_q++;
		line_cpy++;
	}
	if (double_q % 2 == 0 && single_q % 2 == 0)
		return (1);
	return (0);
}

char	**tokenizator(char *line)
{
	int		i;
	int		token_count;
	char	**result;

	i = 0;
	token_count = count_tokens(line);
	result = malloc((token_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*line && *line == ' ')
		line++;
	while (i < token_count)
	{
		result[i] = extract_token(&line);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[token_count] = NULL;
	return (result);
}

void	print_list_state(t_minishell *minishell)
{
	t_cmd	*current;
	int		cmd_index;
	int		arg_index;

	current = minishell->cmd;
	cmd_index = 0;
	while (current != NULL)
	{
		printf("Command %d:\n", cmd_index);
		arg_index = 0;
		while (current->cmd[arg_index] != NULL)
		{
			printf("  Arg %d: %s, in %d out %d\n", arg_index,
				current->cmd[arg_index], current->infile, current->outfile);
			arg_index++;
		}
		current = current->next;
		cmd_index++;
	}
}

void	lexer_main(t_minishell *minishell, char *line)
{
	char	**tokens;
	char	**cp_tokens;

	if (!quote_counter(line))
		printf("exit code 258\n"); // for easy findable syntax error
	tokens = tokenizator(line);
	if (!tokens)
		exit_fail("Failed to allocate memory for tokens");
	cp_tokens = tokens;
	tokens = expander_main(minishell, tokens);
	parser_main(minishell, cp_tokens);
	print_list_state(minishell);
}
