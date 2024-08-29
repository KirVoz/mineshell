#include "minishell.h"

int	count_tokens(const char *line)
{
	int		count;
	int		in_token;
	char	quote;

	count = 0;
	in_token = 0;
	quote = 0;
	while (*line)
	{
		if (quote && *line == quote)
			quote = 0;
		else if (!quote && ft_strchr(QUOTES, *line))
			quote = *line;
		else if (!quote && is_delimiter(line))
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

char	*extract_token(const char **line)
{
	const char	*start;
	char		*token;
	char		quote;
	int			len;

	start = getting_start(line, &quote, &len);
	token = getting_token(start, len);
	while (**line && **line == ' ')
		(*line)++;
	return (token);
}

char	*getting_start(const char **line, char *quote, int *len)
{
	const char	*start;

	*quote = 0;
	*len = 0;
	start = *line;
	while (**line)
	{
		if (*quote && **line == *quote)
			*quote = 0;
		else if (!*quote && ft_strchr(QUOTES, **line))
			*quote = **line;
		else if (!*quote && is_delimiter(*line))
		{
			if (*len > 0)
				break ;
			if (ft_strchr(DELIMS, **line))
			{
				*len = 1;
				(*line)++;
				break ;
			}
		}
		(*len)++;
		(*line)++;
	}
	return ((char *)start);
}

char	*getting_token(const char *start, int len)
{
	char	*token;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1);
	return (token);
}

int	is_delimiter(const char *line)
{
	if (*line == ' ' || ft_strchr(DELIMS, *line) != NULL 
	|| ((*line == '<' || *line == '>') && *(line + 1) == *line))
		return (1);
	return (0);
}
