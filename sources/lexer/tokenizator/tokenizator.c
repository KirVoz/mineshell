#include "lexer.h"
#include "minishell.h"

char	*extract_token(char **line)
{
	char	*start;
	char	*token;
	int		len;

	start = *line;
	len = 0;
	start = getting_start(line, start, &len);
	token = getting_token(start, len);
	while (**line && **line == ' ')
		(*line)++;
	return (token);
}

char	*getting_token(char *start, int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	return (token);
}

char	*find_end_quote_len(char *line, int *len)
{
	int		i;
	char	quote;

	i = 1;
	quote = *line;
	while (line[i] && line[i] != quote)
	{
		i++;
		(*len)++;
	}
	*len += 2;
	return (&(line[i + 1]));
}

char	*getting_start(char **line, char *start, int *len)
{
	while (*line)
	{
		if (ft_strchr(QUOTES, **line))
		{
			if (*len == 0)
				*line = find_end_quote_len(*line, len);
			break ;
		}
		else if (is_delimiter(*line))
		{
			if (*len == 0)
			{
				(*line)++;
				(*len)++;
			}
			break ;
		}
		(*len)++;
		(*line)++;
	}
	return (start);
}
