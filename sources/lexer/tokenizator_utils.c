#include "lexer.h"
#include "minishell.h"

char	*find_end_quote(char *line, int *count)
{
	char	quote;
	int		quotes_before_delimetter;
	int		i;

	quote = *line;
	quotes_before_delimetter = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == quote)
			quotes_before_delimetter++;
		if (ft_strchr(DELIMS, line[i]) && quotes_before_delimetter % 2 == 0)
			break ;
		i++;
	}
	while (!(line[i] == quote) || !line[i])
		i--;
	if (count)
		(*count)++;
	if (!count)
		return (&(line[i + 1]));
	return (&(line[i]));
}

int	find_quotation_len(char *line)
{
	char	quote;
	int		quotes_before_delimetter;
	int		i;

	quote = *line;
	quotes_before_delimetter = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == quote)
			quotes_before_delimetter++;
		if (ft_strchr(DELIMS, line[i]) && quotes_before_delimetter % 2 == 0)
			break ;
		i++;
	}
	while (!(line[i] == quote) || !line[i])
		i--;
	return (i + 1);
}

int	count_tokens(char *line)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*line)
	{
		if (ft_strchr(QUOTES, *line))
			line = find_end_quote(line, &count);
		else if (is_delimiter(line))
		{
			if (in_token)
				in_token = 0;
			if (ft_strchr(DELIMS, *line))
				count++;
		}
		else if (!in_token)
		{
			in_token = 1;
			count++;
		}
		line++;
	}
	return (count);
}

int	is_delimiter(char *line)
{
	if (*line == ' ' || ft_strchr(DELIMS, *line) != NULL || ((*line == '<'
				|| *line == '>') && *(line + 1) == *line))
		return (1);
	return (0);
}
