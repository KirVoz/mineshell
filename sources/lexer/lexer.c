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

void	lexer_main(t_minishell *minishell, char *line)
{
	char	**tokens;
	char	**tokenss;

	(void)minishell;
	if (!quote_counter(line))
		printf("exit code 258\n"); // for easy findable syntax error
	tokens = tokenizator(line);
	if (!tokens)
		exit_fail("Failed to allocate memory for tokens");
	tokenss = tokens;
	tokens = expander(minishell, tokens);
	parser(minishell, tokenss);

	t_list 	*a = minishell->cmd->cmd;
	while (a != NULL)
	{
		printf("%s\n", (char *)a->content);
		a = a->next;
	}
	// while (*tokenss)
	// {
	// 	printf("tokenss %s\n", *tokenss); // printf to see tokenisation
	// 	tokenss++; // добавить в структуру cmd->m_av
	// }
}
