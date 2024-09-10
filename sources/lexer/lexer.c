#include "lexer.h"
#include "minishell.h"

char	*quote_counter(char *line)
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
	if (double_q % 2 != 0)
		return ("\"");
	else if (single_q % 2 != 0)
		return ("'");
	return (NULL);
}

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

int	lexer_main(t_minishell *minishell, char *line)
{
	char	**tokens;

	if (quote_counter(line))
		return (syntax_quote_error(minishell, quote_counter(line)));
	// if (ft_strncmp(line, "<<", ft_strlen(line) == 0))
	// 	line = heredoc_main(line);
	tokens = tokenizator(line);
	expander_main(minishell, tokens);
	if (!validator_main(minishell, &tokens))
		return (0);
	print_tokens_state(tokens, "after validator");
	parser_main(&minishell, &tokens);
	print_list_state(minishell, "after parser");
	return (1);
}
