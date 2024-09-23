#include "lexer.h"
#include "minishell.h"

char	*extract_token(char **line, int i)
{
	char	*start;
	char	*token;
	char	*token_tmp;
	int		len;

	start = *line;
	len = 0;
	start = getting_start(line, start, &len);
	token = getting_token(start, len);
	while (**line && **line == ' ')
		(*line)++;
	if (!ft_strchr(DELIMS, *token) && *(*line - 1)
		&& *(*line - 1) == ' ' && i != 0)
	{
		token_tmp = token;
		token = ft_strjoin(token, " ");
		if (!token)
			exit_fail("Tokens in extract_token");
		free(token_tmp);
	}
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
