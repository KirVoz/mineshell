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
		if (ft_strchr(line_cpy, '"'))
			double_q++;
		else if (ft_strchr(line_cpy, '\''))
			single_q++;
		line_cpy++;
	}
	if (double_q % 2 == 0 && single_q % 2 == 0)
		return (1);
	return (0);
}

char	**tokenisator(const char *line)
{
	int		i;
	int		token_count;
	char	**result;

	i = 0;
	token_count = count_tokens(line);
	result = malloc((token_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
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

	if (!quote_counter(line))
		printf("exit code 258\n"); // for easy findable syntax error
	tokens = tokenisator(line);
    if (!tokens)
    {
		perror("Failed to allocate memory tokens");
		exit(EXIT_FAILURE);
	}
	tokenss = tokens;
	while (*tokenss)
	{
		printf("%s\n", *tokenss); // printf to see tokenisation
		tokenss++; // добавить в структуру cmd->m_av
	}
}
